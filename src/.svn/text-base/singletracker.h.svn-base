#ifndef SINGLETRACKER_H
#define SINGLETRACKER_H
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


#include <string>

#include <QObject>

#include <tobii/sdk/cpp/mainloop.hpp>
#include <tobii/sdk/cpp/discovery/eyetracker-info.hpp>
#include <tobii/sdk/cpp/discovery/eyetracker-browser.hpp>

using namespace tobii::sdk::cpp::discovery;

/**
  * This class listens to browsing events and keep track of a tracker with a specific PID.
  */
class SingleTracker: public QObject
{
    Q_OBJECT

public:
    explicit SingleTracker(const std::string& pid, const tobii::sdk::cpp::mainloop &mainloop);

    bool isFound() const;
    eyetracker_info::pointer get_eyetracker_info() const;

    std::string pid() const;

signals:
    void isFoundChanged(bool isFound);

private:
    void handleBrowserEvent(eyetracker_browser::event_type type, eyetracker_info::pointer et_info);

    eyetracker_browser::pointer browser;
    eyetracker_browser::connection browserConnection;

    std::string m_pid;
    eyetracker_info::pointer m_info;
};

#endif // SINGLETRACKER_H
