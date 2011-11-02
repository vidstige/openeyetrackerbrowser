#ifndef XDATAMODELUNITADAPTER_H
#define XDATAMODELUNITADAPTER_H

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


#include "XDataModel.h"

class XDataModelUnitAdapter
{
public:
    XDataModelUnitAdapter(XDataModel& m);

    double getElevation();
    double getPlaneDist();
    double getPlaneHeight();
    double getPlaneAngle();
    double getPlaneDimWidth();
    double getPlaneDimHeight();
    double getSideOffset();
    double getTrackerPitch();

    bool getUseSideOffset();
    bool getUseTrackerPitch();
    bool getUseTMode();

private:
    double convertToMillimeter(double value);

    XDataModel& model;
};

#endif // XDATAMODELUNITADAPTER_H
