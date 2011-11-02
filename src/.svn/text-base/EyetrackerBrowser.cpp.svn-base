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

#include <QDebug>
#include "EyetrackerBrowser.h"
#include <boost/bind.hpp>

using namespace tobii::sdk::cpp::discovery;

EyetrackerBrowser::EyetrackerBrowser(const tobii::sdk::cpp::mainloop& mainloop,
                                     QObject *parent) :
    QObject(parent),
    browser(new eyetracker_browser(mainloop))
{
    browserConnection = browser->add_browser_event_listener(boost::bind(&EyetrackerBrowser::handleBrowserEvent,this,_1,_2));
    browser->start();
}

void EyetrackerBrowser::handleBrowserEvent(eyetracker_browser::event_type type, eyetracker_info::pointer et_info)
{
    QSharedPointer<EyetrackerBrowserEventArgs> args(new EyetrackerBrowserEventArgs(et_info, type));
    emit browserEvent(args);
}
