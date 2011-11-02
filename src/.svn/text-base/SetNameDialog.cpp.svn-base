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

#include "SetNameDialog.h"
#include "ui_SetNameDialog.h"

#include <QDebug>
#include <QString>
#include <QMessageBox>

#include <string>
#include <tobii/sdk/cpp/discovery/eyetracker-info.hpp>
#include <tobii/sdk/cpp/discovery/factory-info.hpp>
#include <tobii/sdk/cpp/tracking/eyetracker-factory.hpp>
#include <tobii/sdk/cpp/tracking/eyetracker.hpp>
#include <tobii/sdk/cpp/eyetracker-exception.hpp>

#include "unlocker.h"

using namespace tobii::sdk::cpp;
using namespace tobii::sdk::cpp::tracking;
using namespace tobii::sdk::cpp::discovery;

SetNameDialog::SetNameDialog(
    QSharedPointer<EyetrackerBrowserEventArgs> args, MainloopThread& loop,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetNameDialog),
    browserData(args),
    mainloop(loop)
{
    ui->setupUi(this);

    QString name = QString::fromStdString(args->info()->get_given_name());
    ui->nameTextBox->setText(name);
}

SetNameDialog::~SetNameDialog()
{
    delete ui;
}

void SetNameDialog::accept()
{
    try
    {
        factory_info fi(*(browserData->info()));
        eyetracker::pointer tracker = create_eyetracker(fi, mainloop.internalMainloop());
        Unlocker::unlock(tracker);

        std::string newName = ui->nameTextBox->text().toStdString();

        if(newName == "")
        {
            // If name is empty we set the product id as name
            newName = browserData->info()->get_product_id();
        }
        else if(newName.length() > 140)
        {
            // Truncate string if it is longer than 140 chars
            newName = newName.substr(0, 140);
        }

        tracker->set_unit_name(newName);
    }
    catch(const eyetracker_exception& ex)
    {
        qDebug() << "Setting the eyetracker name failed";

        QMessageBox box(this);
        box.setIcon(QMessageBox::Warning);
        box.setText("Failed to set name!");
        box.setWindowTitle("Error");
        box.exec();
    }

    QDialog::accept();
}
