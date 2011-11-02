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

#include "WaitForTrackerDialog.h"
#include "ui_WaitForTrackerDialog.h"

WaitForTrackerDialog::WaitForTrackerDialog(QSharedPointer<SingleTracker> single, QWidget *parent) :
    QDialog(parent), single_tracker(single),
    ui(new Ui::WaitForTrackerDialog), m_accepted(false)
{
    ui->setupUi(this);

    ui->pidLabel->setText(QString::fromStdString(single->pid()));

    connect(single_tracker.data(), SIGNAL(isFoundChanged(bool)), SLOT(acceptOnce()), Qt::QueuedConnection);
}

WaitForTrackerDialog::~WaitForTrackerDialog()
{
    delete ui;
}

void WaitForTrackerDialog::acceptOnce()
{
    if (!m_accepted)
    {
        m_accepted = true;
        accept();
    }
}
