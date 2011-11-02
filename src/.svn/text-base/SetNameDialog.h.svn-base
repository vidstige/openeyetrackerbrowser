#ifndef SETNAMEDIALOG_H
#define SETNAMEDIALOG_H

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
#include <QSharedPointer>
#include "EyetrackerBrowserEventArgs.h"
#include "MainloopThread.h"

namespace Ui {
    class SetNameDialog;
}

class SetNameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetNameDialog(
        QSharedPointer<EyetrackerBrowserEventArgs> args,
        MainloopThread& loop,
        QWidget *parent = 0);
    ~SetNameDialog();

public slots:
    virtual void accept();

private:
    Ui::SetNameDialog *ui;
    QSharedPointer<EyetrackerBrowserEventArgs> browserData;
    MainloopThread& mainloop;
};

#endif // SETNAMEDIALOG_H
