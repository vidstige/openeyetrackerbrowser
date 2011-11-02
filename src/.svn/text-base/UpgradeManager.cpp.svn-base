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

#include "UpgradeManager.h"

#include <boost/bind.hpp>
#include <tobii/sdk/cpp/upgrade/upgrade.hpp>
#include <QDebug>

using namespace tobii::sdk::cpp::upgrade;
using namespace tobii::sdk::cpp::discovery;

UpgradeManager::UpgradeManager(MainloopThread& loop, QObject *parent) :
    QObject(parent),
    mainloop(loop)
{
    progressConnection = progressReporter.add_progress_changed_listener(boost::bind(&UpgradeManager::progressChangedHandler,this,_1));
    completedConnection = progressReporter.add_upgrade_completed_listener(boost::bind(&UpgradeManager::upgradeCompletedHandler, this, _1));
}

void UpgradeManager::startUpgrade(const upgrade_package &upgradePackage, const eyetracker_info &etInfo)
{
    begin_upgrade(mainloop.internalMainloop(), upgradePackage, etInfo, progressReporter);
}

void UpgradeManager::upgradeCompletedHandler(uint32_t result)
{
    emit upgradeCompleted((int)result);
}

void UpgradeManager::progressChangedHandler(progress_reporter::progress progress)
{
    int currentValue = (progress.current_step*100 + progress.percent) / progress.number_of_steps;
    emit progressUpdate(currentValue);
}
