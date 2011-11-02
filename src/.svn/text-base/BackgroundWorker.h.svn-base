#ifndef BACKGROUNDWORKER_H
#define BACKGROUNDWORKER_H

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

#include <QThread>
#include <QSharedPointer>
#include "EyetrackerBrowserEventArgs.h"
#include "TrackerProperties.h"
#include "MainloopThread.h"

class BackgroundWorker : public QThread
{
    Q_OBJECT
public:
    explicit BackgroundWorker(MainloopThread& loop,QObject *parent = 0);
    virtual ~BackgroundWorker();

signals:
    void trackerPropertiesResolved(TrackerProperties);
    void debugMovieCaptureProgress(int, int);
    void diagnosticsDataSaved(bool);

public slots:
    void resolveTrackerProperties(QSharedPointer<EyetrackerBrowserEventArgs> args);
    void setFrameRate(QSharedPointer<EyetrackerBrowserEventArgs> args, float framerate);
    void setIlluminationMode(QSharedPointer<EyetrackerBrowserEventArgs> args, TrackerProperties::IlluminationMode mode, QString custom);
    void getDiagnostics(QSharedPointer<EyetrackerBrowserEventArgs> args, bool includeImages, QString path);
protected:
    virtual void run();

private:
    MainloopThread& mainloop;

};

#endif // BACKGROUNDWORKER_H
