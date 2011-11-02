#ifndef UPGRADEMANAGER_H
#define UPGRADEMANAGER_H

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


#include <QObject>
#include <tobii/sdk/cpp/eyetracker-exception.hpp>
#include <tobii/sdk/cpp/discovery/eyetracker-info.hpp>
#include <tobii/sdk/cpp/upgrade/progress-reporter.hpp>
#include <tobii/sdk/cpp/upgrade/upgrade-package.hpp>
#include "MainloopThread.h"

class UpgradeManager : public QObject
{
    Q_OBJECT
public:
    explicit UpgradeManager(MainloopThread& loop, QObject *parent = 0);

    void startUpgrade(const tobii::sdk::cpp::upgrade::upgrade_package& upgradePackage,
                      const tobii::sdk::cpp::discovery::eyetracker_info& etInfo);

signals:
    void progressUpdate(int);
    void upgradeCompleted(int);

public slots:

private:
    void progressChangedHandler(tobii::sdk::cpp::upgrade::progress_reporter::progress progress);
    void upgradeCompletedHandler(uint32_t result);

    MainloopThread& mainloop;
    tobii::sdk::cpp::upgrade::progress_reporter progressReporter;
    tobii::sdk::cpp::upgrade::progress_reporter::connection completedConnection;
    tobii::sdk::cpp::upgrade::progress_reporter::connection progressConnection;
};

#endif // UPGRADEMANAGER_H
