#ifndef WAITFORTRACKERDIALOG_H
#define WAITFORTRACKERDIALOG_H

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

#include "singletracker.h"

namespace Ui {
    class WaitForTrackerDialog;
}

class WaitForTrackerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WaitForTrackerDialog(QSharedPointer<SingleTracker> single, QWidget *parent = 0);
    ~WaitForTrackerDialog();

private slots:
    void acceptOnce();
private:
    bool m_accepted;

    Ui::WaitForTrackerDialog *ui;

    QSharedPointer<SingleTracker> single_tracker;
};

#endif // WAITFORTRACKERDIALOG_H
