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
#include <QDebug>

XDataModel::XDataModel(QObject *parent) :
    QObject(parent),
    unit(XDataModel::CM),
    elevation(0.0),
    planeDist(0.0),
    planeHeight(0.0),
    planeAngle(0.0),
    planeDimWidth(0.0),
    planeDimHeight(0.0),
    sideOffset(0.0),
    trackerPitch(0.0),
    useSideOffset(false),
    useTrackerPitch(false),
    useTMode(false)
{
}

// Getters

double XDataModel::getElevation()
{
    return elevation;
}

double XDataModel::getPlaneDist()
{
    return planeDist;
}

double XDataModel::getPlaneHeight()
{
    return planeHeight;
}


double XDataModel::getPlaneAngle()
{
    return planeAngle;
}

double XDataModel::getPlaneDimWidth()
{
    return planeDimWidth;
}

double XDataModel::getPlaneDimHeight()
{
    return planeDimHeight;
}

double XDataModel::getSideOffset()
{
    if(useSideOffset)
    {
        return sideOffset;
    }
    else
    {
        return 0.0;
    }
}


double XDataModel::getTrackerPitch()
{
    if(useTrackerPitch)
    {
        return trackerPitch;
    }
    else
    {
        return 0.0;
    }
}


bool XDataModel::getUseSideOffset()
{
    return useSideOffset;
}

bool XDataModel::getUseTrackerPitch()
{
    return useTrackerPitch;
}

bool XDataModel::getUseTMode()
{
    return useTMode;
}

XDataModel::LengthUnit XDataModel::getLengthUnit()
{
    return unit;
}

// Converters

double XDataModel::convertCmToInch(double cmLength)
{
    return cmLength / 2.54;
}

double XDataModel::convertInchToCm(double inchLength)
{
    return inchLength * 2.54;
}



// Slots

void XDataModel::setElevation(double value)
{
    if(value != elevation)
    {
        elevation = value;
        emit modelChanged();
    }
}

void XDataModel::setPlaneDist(double value)
{
    if(value != planeDist)
    {
        planeDist = value;
        emit modelChanged();
    }
}

void XDataModel::setPlaneHeight(double value)
{
    if(value != planeHeight)
    {
        planeHeight = value;
        emit modelChanged();
    }
}

void XDataModel::setPlaneAngle(double value)
{
    if(value != planeAngle)
    {
        planeAngle = value;
        emit modelChanged();
    }
}



void XDataModel::setPlaneDimWidth(double value)
{
    if(value != planeDimWidth)
    {
        planeDimWidth = value;
        emit modelChanged();
    }
}

void XDataModel::setPlaneDimHeight(double value)
{
    if(value != planeDimHeight)
    {
        planeDimHeight = value;
        emit modelChanged();
    }
}

void XDataModel::setSideOffset(double value)
{
    if(value != sideOffset)
    {
        sideOffset = value;
        emit modelChanged();
    }
}

void XDataModel::setTrackerPitch(double value)
{
    if(value != trackerPitch)
    {
        trackerPitch = value;
        emit modelChanged();
    }

}

void XDataModel::setUseSideOffset(bool value)
{
    if(value != useSideOffset)
    {
        useSideOffset = value;
        emit modelChanged();
    }
}

void XDataModel::setUseTrackerPitch(bool value)
{
    if(value != useTrackerPitch)
    {
        useTrackerPitch = value;
        emit modelChanged();
    }
}

void XDataModel::setUseTMode(bool value)
{
    if(value != useTMode)
    {
        useTMode = value;
        emit modelChanged();
    }
}

void XDataModel::setLengthUnit(LengthUnit value)
{
    if(value != unit)
    {
        unit = value;

        if(unit == CM)
        {
            planeDist = convertInchToCm(planeDist);
            planeHeight = convertInchToCm(planeHeight);
            planeDimWidth = convertInchToCm(planeDimWidth);
            planeDimHeight = convertInchToCm(planeDimHeight);
            sideOffset = convertInchToCm(sideOffset);
        }
        else
        {
            planeDist = convertCmToInch(planeDist);
            planeHeight = convertCmToInch(planeHeight);
            planeDimWidth = convertCmToInch(planeDimWidth);
            planeDimHeight = convertCmToInch(planeDimHeight);
            sideOffset = convertCmToInch(sideOffset);
        }

        emit modelChanged();
    }
}

void XDataModel::printModel()
{
    qDebug() << "Length Unit " << unit;
    qDebug() << "Elevation " << elevation;

    qDebug() << "planeDist " << planeDist;
    qDebug() << "planeHeight " << planeHeight;
    qDebug() << "planeAngle " << planeAngle;
    qDebug() << "planeDimWith " << planeDimWidth;
    qDebug() << "planeDimHeight " << planeDimHeight;
    qDebug() << "sideOffset " << sideOffset;
    qDebug() << "trackerPitch " << trackerPitch;

    qDebug() << "useSideOffset " << useSideOffset;
    qDebug() << "useTrackerPitch " << useTrackerPitch;
}


