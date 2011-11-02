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

#include "singletracker.h"

SingleTracker::SingleTracker(const std::string& pid, const tobii::sdk::cpp::mainloop &mainloop):
    m_pid(pid), browser(new eyetracker_browser(mainloop))
{
    browserConnection = browser->add_browser_event_listener(boost::bind(&SingleTracker::handleBrowserEvent,this,_1,_2));
    browser->start();
}

bool SingleTracker::isFound() const
{
    return m_info != 0;
}

eyetracker_info::pointer SingleTracker::get_eyetracker_info() const
{
    return m_info;
}

std::string SingleTracker::pid() const
{
    return m_pid;
}

void SingleTracker::handleBrowserEvent(eyetracker_browser::event_type type, eyetracker_info::pointer et_info)
{
    if (et_info->get_product_id() == m_pid)
    {
        if (type == eyetracker_browser::TRACKER_FOUND || type == eyetracker_browser::TRACKER_UPDATED)
        {
            m_info = et_info;
            emit isFoundChanged(isFound());
        }
        else
        {
            m_info.reset();
            emit isFoundChanged(isFound());
        }
    }
}
