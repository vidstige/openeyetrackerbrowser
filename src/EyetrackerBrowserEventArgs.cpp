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

#include "EyetrackerBrowserEventArgs.h"
#include <tobii/sdk/cpp/eyetracker-exception.hpp>
#include <tobii/sdk/core.h>
#include <vector>
#include <QDebug>

using namespace tobii::sdk::cpp;
using namespace tobii::sdk::cpp::tracking;

EyetrackerBrowserEventArgs::EyetrackerBrowserEventArgs(
    tobii::sdk::cpp::discovery::eyetracker_info::pointer info,
    tobii::sdk::cpp::discovery::eyetracker_browser::event_type type,
    QObject *parent) :
    QObject(parent),
    internalInfo(info),
    internalType(type)
{
}


tobii::sdk::cpp::discovery::eyetracker_browser::event_type EyetrackerBrowserEventArgs::type()
{
    return internalType;
}

tobii::sdk::cpp::discovery::eyetracker_info::pointer EyetrackerBrowserEventArgs::info()
{
    return internalInfo;
}
