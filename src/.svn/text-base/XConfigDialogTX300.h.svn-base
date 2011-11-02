#ifndef XCONFIGDIALOGTX300_H
#define XCONFIGDIALOGTX300_H

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

#include <tobii/sdk/cpp/discovery/eyetracker-info.hpp>

#include "EyetrackerBrowserEventArgs.h"
#include "XDataModel.h"
#include "XDataSaver.h"
#include "MainloopThread.h"

namespace Ui {
    class XConfigDialogTX300;
}

using namespace tobii::sdk::cpp::discovery;

class XConfigDialogTX300 : public QDialog
{
    Q_OBJECT

public:
    explicit XConfigDialogTX300(eyetracker_info::pointer info, MainloopThread& loop, QWidget *parent = 0);
    ~XConfigDialogTX300();

protected:
    virtual void closeEvent(QCloseEvent *event);

private slots:
    void updateUserInterface();
    void lengthUnitToggled(bool value);
    void saveToFile();
    void loadFromFile();
    void saveToTracker();

private:
    eyetracker_info::pointer _info;
    Ui::XConfigDialogTX300 *ui;
    XDataModel model;
    XDataSaver saver;
    MainloopThread& mainloop;
    XDataSaver::TrackerType trackerType;
};

#endif // XCONFIGDIALOGTX300_H
