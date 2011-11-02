#ifndef XDATASAVER_H
#define XDATASAVER_H

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


#include "MathTypes.h"
#include "XDataModel.h"
#include "MainloopThread.h"
#include <tobii/sdk/cpp/discovery/eyetracker-info.hpp>

class XDataSaver
{
public:

    enum TrackerType
    {
        X120,
        TX300,
        ISFM
    };

    XDataSaver();

    bool isSavedToTracker(XDataModel& model, TrackerType type);

    bool saveToTracker(
        XDataModel &model, TrackerType type,
        tobii::sdk::cpp::discovery::eyetracker_info::pointer eyetracker,
        MainloopThread& mainloop);

private:

    void computeParameters(XDataModel& model, TrackerType type, SpaceVector& posUL, SpaceVector& posUR, SpaceVector& posLL);

    bool dataSaved;
    SpaceVector savedUL;
    SpaceVector savedUR;
    SpaceVector savedLL;

};

#endif // XDATASAVER_H
