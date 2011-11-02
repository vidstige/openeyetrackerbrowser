#ifndef EYETRACKERBROWSERAPPLICATION_H
#define EYETRACKERBROWSERAPPLICATION_H

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


#include <QApplication>

#include "MainloopThread.h"

#include "mainwindow.h"
#include "WaitForTrackerDialog.h"

class EyeTrackerBrowserApplication : public QApplication
{
    Q_OBJECT
public:
    EyeTrackerBrowserApplication(int& argc, char ** argv);

    virtual ~EyeTrackerBrowserApplication();

    // reimplemented from QApplication so we can throw exceptions in slots
    virtual bool notify(QObject * receiver, QEvent * event);

    QWidget* startWindow();

private slots:
    void eyetrackerFound();

private:
    void createMainWindow();

    MainloopThread m_mainloopThread;
    MainWindow* m_mainWindow;
    WaitForTrackerDialog* m_waitWindow;
    QSharedPointer<SingleTracker> single;
};

#endif // EYETRACKERBROWSERAPPLICATION_H
