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

#include "XDataFile.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

XDataFile::XDataFile()
{
}

bool XDataFile::saveToFile(XDataModel &model, QString fileName)
{
    QFile file(fileName);
    if(file.open(QFile::Truncate | QFile::WriteOnly))
    {
        QTextStream stream(&file);

        stream << "XDATA" << '\n';
        stream << "1" << '\n'; // Version

        stream << (int) model.getLengthUnit() << '\n';

        stream << model.getElevation() << '\n';
        stream << model.getPlaneAngle() << '\n';
        stream << model.getPlaneDimHeight() << '\n';
        stream << model.getPlaneDimWidth() << '\n';
        stream << model.getPlaneDist() << '\n';
        stream << model.getPlaneHeight() << '\n';
        stream << model.getSideOffset() << '\n';
        stream << model.getTrackerPitch() << '\n';

        stream << (int)model.getUseSideOffset() << '\n';
        stream << (int)model.getUseTrackerPitch() << '\n';

        stream.flush();

        return true;
    }
    else
    {
        return false;
    }
}

bool XDataFile::readFromFile(XDataModel &model, QString fileName)
{
    QFile file(fileName);
    if(file.open(QFile::ReadOnly))
    {
        QTextStream stream(&file);

        QString header;
        QString version;

        int unitInt;
        XDataModel::LengthUnit unit;

        double elevation;
        double planeAngle;
        double planeDimHeight;
        double planeDimWidth;
        double planeDist;
        double planeHeight;
        double sideOffset;
        double trackerPitch;

        int useSideOffset;
        int useTrackerPitch;

        stream >> header;
        stream >> version;

        if(header != "XDATA")
            return false;

        if(version != "1")
            return false;

        stream >> unitInt;
        unit = (XDataModel::LengthUnit)unitInt;

        if(!(unit == XDataModel::CM || unit == XDataModel::INCH))
        {
            qDebug() << "Invalid file content: Unknown length unit";
            return false;
        }

        stream >> elevation;
        stream >> planeAngle;
        stream >> planeDimHeight;
        stream >> planeDimWidth;
        stream >> planeDist;
        stream >> planeHeight;
        stream >> sideOffset;
        stream >> trackerPitch;
        stream >> useSideOffset;
        stream >> useTrackerPitch;


        model.setLengthUnit(unit); // Important! Set length unit first
        model.setElevation(elevation);
        model.setPlaneAngle(planeAngle);
        model.setPlaneDimHeight(planeDimHeight);
        model.setPlaneDimWidth(planeDimWidth);
        model.setPlaneDist(planeDist);
        model.setPlaneHeight(planeHeight);
        model.setSideOffset(sideOffset);
        model.setTrackerPitch(trackerPitch);
        model.setUseSideOffset((bool)useSideOffset);
        model.setUseTrackerPitch((bool)useTrackerPitch);

        return true;
    }
    else
    {
        return false;
    }
}
