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

#include "UpgradeDialog.h"
#include "ui_UpgradeDialog.h"

#include <QCloseEvent>

UpgradeDialog::UpgradeDialog(MainloopThread& mainloop, QWidget *parent) :
    QDialog(parent),
    upgradeManager(mainloop),
    ui(new Ui::UpgradeDialog)
{
    ui->setupUi(this);

    setFixedSize(size());

    connect(&upgradeManager, SIGNAL(progressUpdate(int)), this, SLOT(updateProgress(int)), Qt::QueuedConnection);
    connect(&upgradeManager, SIGNAL(upgradeCompleted(int)), this, SLOT(upgradeCompleted(int)), Qt::QueuedConnection);
}

UpgradeDialog::~UpgradeDialog()
{
    delete ui;
}

void UpgradeDialog::startUpgrade(const tobii::sdk::cpp::upgrade::upgrade_package &upgradePackage,
                                 const tobii::sdk::cpp::discovery::eyetracker_info &etInfo)
{
    upgradeManager.startUpgrade(upgradePackage, etInfo);
}

void UpgradeDialog::updateProgress(int progress)
{
    if(ui->progressBar->value() != progress)
    {
        ui->progressBar->setValue(progress);
    }
}


void UpgradeDialog::upgradeCompleted(int result)
{
    ui->okButton->setEnabled(true);

    if(result) {
        ui->label->setText("Upgrade Failed!");
    }
    else {
        ui->label->setText("Upgrade Completed!");
    }
}

void UpgradeDialog::closeEvent(QCloseEvent *event)
{
    // Prevent closing of the dialog if we haven't finished
    if(ui->okButton->isEnabled())
    {
        event->accept();
    }
    else {
        event->ignore();
    }
}
