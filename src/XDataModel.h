#ifndef XDATAMODEL_H
#define XDATAMODEL_H

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

class XDataModel : public QObject
{
    Q_OBJECT
public:
    explicit XDataModel(QObject *parent = 0);


    enum LengthUnit
    {
        CM,
        INCH
    };

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

    LengthUnit getLengthUnit();

signals:
    void modelChanged();

public slots:
    void setElevation(double value);
    void setPlaneDist(double value);
    void setPlaneHeight(double value);
    void setPlaneAngle(double value);
    void setPlaneDimWidth(double value);
    void setPlaneDimHeight(double value);
    void setSideOffset(double value);
    void setTrackerPitch(double value);

    void setUseSideOffset(bool value);
    void setUseTrackerPitch(bool value);
    void setUseTMode(bool value);

    void setLengthUnit(LengthUnit value);

    void printModel();

private:

    double convertCmToInch(double cmLength);
    double convertInchToCm(double inchLength);

    LengthUnit unit;

    double elevation;
    double planeDist;
    double planeHeight;
    double planeAngle;
    double planeDimWidth;
    double planeDimHeight;
    double sideOffset;
    double trackerPitch;

    bool useSideOffset;
    bool useTrackerPitch;
    bool useTMode;

};

#endif // XDATAMODEL_H
