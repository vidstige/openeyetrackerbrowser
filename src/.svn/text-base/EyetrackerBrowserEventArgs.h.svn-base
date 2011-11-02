#ifndef EYETRACKERBROWSEREVENTARGS_H
#define EYETRACKERBROWSEREVENTARGS_H

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
#include <tobii/sdk/cpp/discovery/eyetracker-browser.hpp>
#include <tobii/sdk/cpp/discovery/eyetracker-info.hpp>
#include <tobii/sdk/cpp/tracking/eyetracker.hpp>


class EyetrackerBrowserEventArgs : public QObject
{
    Q_OBJECT
public:
    explicit EyetrackerBrowserEventArgs(
        tobii::sdk::cpp::discovery::eyetracker_info::pointer info,
        tobii::sdk::cpp::discovery::eyetracker_browser::event_type type,
        QObject *parent = 0);

    tobii::sdk::cpp::discovery::eyetracker_browser::event_type type();
    tobii::sdk::cpp::discovery::eyetracker_info::pointer info();

signals:

public slots:

private:
    tobii::sdk::cpp::discovery::eyetracker_info::pointer internalInfo;
    tobii::sdk::cpp::discovery::eyetracker_browser::event_type internalType;
};

#endif // EYETRACKERBROWSEREVENTARGS_H
