#ifndef UPGRADEDIALOG_H
#define UPGRADEDIALOG_H

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


#include <QDialog>

#include "MainloopThread.h"
#include "UpgradeManager.h"

#include <tobii/sdk/cpp/upgrade/upgrade-package.hpp>
#include <tobii/sdk/cpp/discovery/eyetracker-info.hpp>

namespace Ui {
    class UpgradeDialog;
}

class UpgradeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpgradeDialog(MainloopThread& mainloop, QWidget *parent = 0);
    ~UpgradeDialog();

    void startUpgrade(const tobii::sdk::cpp::upgrade::upgrade_package& upgradePackage,
                      const tobii::sdk::cpp::discovery::eyetracker_info& etInfo);
protected:
    virtual void closeEvent(QCloseEvent *event);


private slots:
    void updateProgress(int progress);
    void upgradeCompleted(int result);
private:
    UpgradeManager upgradeManager;
    Ui::UpgradeDialog *ui;
};

#endif // UPGRADEDIALOG_H
