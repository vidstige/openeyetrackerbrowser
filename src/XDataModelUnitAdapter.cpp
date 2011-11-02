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

#include "XDataModelUnitAdapter.h"

XDataModelUnitAdapter::XDataModelUnitAdapter(XDataModel &m) :
    model(m)
{
}

double XDataModelUnitAdapter::getElevation()
{
    return model.getElevation();
}

double XDataModelUnitAdapter::getPlaneDist()
{
    return convertToMillimeter(model.getPlaneDist());
}

double XDataModelUnitAdapter::getPlaneHeight()
{
    return convertToMillimeter(model.getPlaneHeight());
}

double XDataModelUnitAdapter::getPlaneAngle()
{
    return model.getPlaneAngle();
}

double XDataModelUnitAdapter::getPlaneDimWidth()
{
    return convertToMillimeter(model.getPlaneDimWidth());
}

double XDataModelUnitAdapter::getPlaneDimHeight()
{
    return convertToMillimeter(model.getPlaneDimHeight());
}

double XDataModelUnitAdapter::getSideOffset()
{
    return convertToMillimeter(model.getSideOffset());
}

double XDataModelUnitAdapter::getTrackerPitch()
{
    return model.getTrackerPitch();
}

bool XDataModelUnitAdapter::getUseSideOffset()
{
    return model.getUseSideOffset();
}

bool XDataModelUnitAdapter::getUseTrackerPitch()
{
    return model.getUseTrackerPitch();
}

bool XDataModelUnitAdapter::getUseTMode()
{
    return model.getUseTMode();
}

double XDataModelUnitAdapter::convertToMillimeter(double value)
{
    if(model.getLengthUnit() == XDataModel::CM)
    {
        return 10.0 * value;
    }
    else
    {
        return 25.4 * value;
    }
}

