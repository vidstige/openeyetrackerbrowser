#ifndef EYETRACKERBROWSER_H
#define EYETRACKERBROWSER_H

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
#include <QSharedPointer>
#include <tobii/sdk/cpp/discovery/eyetracker-browser.hpp>
#include "EyetrackerBrowserEventArgs.h"

class EyetrackerBrowser : public QObject
{
    Q_OBJECT
public:
    explicit EyetrackerBrowser(const tobii::sdk::cpp::mainloop& mainloop, QObject *parent = 0);

signals:
    void browserEvent(QSharedPointer<EyetrackerBrowserEventArgs>);

public slots:

private:
    void handleBrowserEvent(tobii::sdk::cpp::discovery::eyetracker_browser::event_type type,
                       tobii::sdk::cpp::discovery::eyetracker_info::pointer et_info);

    tobii::sdk::cpp::discovery::eyetracker_browser::pointer browser;
    tobii::sdk::cpp::discovery::eyetracker_browser::connection browserConnection;
};

#endif // EYETRACKERBROWSER_H
