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

#include <string>
#include <QSharedPointer>
#include <QMessageBox>

#include <tobii/sdk/cpp/mainloop.hpp>
#include <tobii/sdk/cpp/eyetracker-exception.hpp>

#include "EyeTrackerBrowserApplication.h"
#include "AppVersion.hpp"
#include "singletracker.h"

#include "mainwindow.h"
#include "XConfigDialogTX300.h"
#include "WaitForTrackerDialog.h"

EyeTrackerBrowserApplication::EyeTrackerBrowserApplication(int& argc, char ** argv):
    QApplication(argc, argv), m_mainWindow(0), m_waitWindow(0)
{
    setApplicationVersion(VERSION_NUMBER);
}

EyeTrackerBrowserApplication::~EyeTrackerBrowserApplication()
{
    delete m_waitWindow;
    delete m_mainWindow;
}

// reimplemented from QApplication so we can throw exceptions in slots
bool EyeTrackerBrowserApplication::notify(QObject * receiver, QEvent * event)
{
    try {
        return QApplication::notify(receiver, event);
    }
    catch (const tobii::sdk::cpp::eyetracker_exception& ex)
    {
        QMessageBox msgBox;
        msgBox.setText(ex.what());
        msgBox.exec();
    }
    return false;
}

void EyeTrackerBrowserApplication::eyetrackerFound()
{
    XConfigDialogTX300 toolDialog(single->get_eyetracker_info(), m_mainloopThread);
    toolDialog.exec();
}

QWidget* EyeTrackerBrowserApplication::startWindow()
{
    if (m_mainWindow == 0)
    {
        createMainWindow();
    }
    if (m_waitWindow != 0) return m_waitWindow;
    return m_mainWindow;
}

void EyeTrackerBrowserApplication::createMainWindow()
{
    m_mainWindow = new MainWindow(m_mainloopThread);

    if (arguments().length() > 1)
    {
        std::string pid = arguments().at(1).toStdString();

        single = QSharedPointer<SingleTracker>(new SingleTracker(pid, m_mainloopThread.internalMainloop()));
        m_waitWindow = new WaitForTrackerDialog(single);
        connect(m_waitWindow, SIGNAL(rejected()), SLOT(quit()));
        connect(m_waitWindow, SIGNAL(accepted()), SLOT(eyetrackerFound()));
    }
    m_mainloopThread.start();
}
