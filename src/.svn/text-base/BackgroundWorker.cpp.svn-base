/* 
   Copyright 2011 Tobii Technology AB

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "BackgroundWorker.h"

#include <QDebug>
#include <QFile>
#include <QDataStream>

#include <vector>
#include <stdexcept>

#include <tobii/sdk/cpp/discovery/eyetracker-info.hpp>
#include <tobii/sdk/cpp/discovery/factory-info.hpp>
#include <tobii/sdk/cpp/tracking/eyetracker-factory.hpp>
#include <tobii/sdk/cpp/tracking/eyetracker.hpp>
#include <tobii/sdk/cpp/eyetracker-exception.hpp>

#include "unlocker.h"

using namespace tobii::sdk::cpp;
using namespace tobii::sdk::cpp::tracking;
using namespace tobii::sdk::cpp::discovery;


BackgroundWorker::BackgroundWorker(MainloopThread& loop, QObject *parent) :
    QThread(parent),
    mainloop(loop)
{
    start();

    // Move ownership of this from the main thread to this thread
    moveToThread(this);
}

BackgroundWorker::~BackgroundWorker()
{
    quit();
    wait(5000);
}

void BackgroundWorker::resolveTrackerProperties(QSharedPointer<EyetrackerBrowserEventArgs> args)
{
    TrackerProperties props;
    props.productId = QString::fromStdString(args->info()->get_product_id());

    // Just try to get properties from units that are OK
    if(args->info()->get_status() != "ok")
        return;

    try
    {
        factory_info fi(*(args->info()));
        eyetracker::pointer tracker = create_eyetracker(fi, mainloop.internalMainloop());

        if(!Unlocker::unlock(tracker))
            return;

        props.currentFramerate = tracker->get_framerate();

        std::vector<float> framerates = tracker->enumerate_framerates();

        for(size_t i=0; i<framerates.size();i++)
        {
            props.framerates.push_back(framerates[i]);
        }

        try
        {
            tracker->enable_extension(1); // 1 is the ID for the low blink extension
            uint32_t lowBlinkEnabled = tracker->get_lowblink_mode();
            props.hasLowblink = true;
            props.lowBlinkEnabled = (bool)lowBlinkEnabled;
        }
        catch(const eyetracker_exception&)
        {
            props.hasLowblink = false;
        }

        if(!props.hasLowblink)
        {
            try
            {
                QString mode = QString::fromStdString(tracker->get_illumination_mode());
                props.currentIlluminationMode = mode;

                std::vector<std::string> allModes = tracker->enumerate_illumination_modes();
                for(size_t i=0; i<allModes.size(); i++)
                {
                    props.illuminationModes.push_back(QString::fromStdString(allModes[i]));
                }

            }
            catch(const eyetracker_exception&)
            {
                props.currentIlluminationMode = "";
            }
        }


        emit trackerPropertiesResolved(props);
    }
    catch(const eyetracker_exception& ex)
    {
        if(ex.get_error_code() == 0x20000402)
        {
            props.unsupportedFirmware = true;
            emit trackerPropertiesResolved(props);
        }
    }
    catch(const std::exception& ex)
    {
        qDebug() << ex.what();
    }
}

void BackgroundWorker::setIlluminationMode(QSharedPointer<EyetrackerBrowserEventArgs> args, TrackerProperties::IlluminationMode mode, QString custom)
{
    try
    {
        factory_info fi(*(args->info()));
        eyetracker::pointer tracker = create_eyetracker(fi, mainloop.internalMainloop());

        if(!Unlocker::unlock(tracker))
            return;

        if(mode == TrackerProperties::Other)
        {
            tracker->set_illumination_mode(custom.toStdString());
        }
        else
        {
            tracker->enable_extension(1); // 1 is the ID for the low blink extension
            if(mode == TrackerProperties::LowBlinkEnabled)
            {
                tracker->set_lowblink_mode(1);
            }
            else if(mode == TrackerProperties::LowBlinkDisabled)
            {
                tracker->set_lowblink_mode(0);
            }
        }

        tracker.reset();

        resolveTrackerProperties(args);
    }
    catch(const eyetracker_exception& ex)
    {
        qDebug() << "Failed to set illumination mode " << (uint)ex.get_error_code();
    }
}


void BackgroundWorker::setFrameRate(QSharedPointer<EyetrackerBrowserEventArgs> args, float framerate)
{
    try
    {
        factory_info fi(*(args->info()));
        eyetracker::pointer tracker = create_eyetracker(fi, mainloop.internalMainloop());

        if(!Unlocker::unlock(tracker))
            return;

        float currentFramerate = tracker->get_framerate();
        if(currentFramerate == framerate)
            return;

        tracker->set_framerate(framerate);
        tracker.reset();

        resolveTrackerProperties(args);
    }
    catch(const eyetracker_exception& ex)
    {
        qDebug() << "Failed to set framerate " << (uint)ex.get_error_code();
    }
}

void BackgroundWorker::getDiagnostics(QSharedPointer<EyetrackerBrowserEventArgs> args, bool includeImages, QString path)
{
    try
    {
        factory_info fi(*(args->info()));
        eyetracker::pointer tracker = create_eyetracker(fi, mainloop.internalMainloop());

        if(!Unlocker::unlock(tracker))
            return;

        if(includeImages)
        {
            const int numImages = 5;
            for(int i=0; i<numImages; i++)
            {
                tracker->dump_images(1, 1);
                emit debugMovieCaptureProgress(i, numImages);
                msleep(700);
            }
        }

        blob diagData = tracker->get_diagnostics_report(includeImages ? 1 : 0);

        QFile file(path);
        if(file.open(QIODevice::WriteOnly))
        {
            QDataStream out(&file);
            out.writeRawData((char *)diagData.get_data().get(), (int)diagData.get_length());
            emit diagnosticsDataSaved(true);
        }
        else
        {
            qDebug() << "Failed to open diagnostics file for saving.";
            emit diagnosticsDataSaved(false);
        }
    }
    catch(const eyetracker_exception& ex)
    {
        qDebug() << "Failed to get diagnostivs data " << (uint)ex.get_error_code();
        emit diagnosticsDataSaved(false);
    }
}

void BackgroundWorker::run()
{
    exec();
}
