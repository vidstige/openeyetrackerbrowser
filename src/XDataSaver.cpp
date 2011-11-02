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

#include "XDataSaver.h"
#include "XDataModelUnitAdapter.h"
#include "unlocker.h"
#include <QDebug>

#include <tobii/sdk/cpp/discovery/eyetracker-info.hpp>
#include <tobii/sdk/cpp/discovery/factory-info.hpp>
#include <tobii/sdk/cpp/tracking/eyetracker-factory.hpp>
#include <tobii/sdk/cpp/tracking/eyetracker.hpp>
#include <tobii/sdk/cpp/eyetracker-exception.hpp>

using namespace tobii::sdk::cpp;
using namespace tobii::sdk::cpp::tracking;
using namespace tobii::sdk::cpp::discovery;


XDataSaver::XDataSaver() :
    dataSaved(false)
{

}

bool XDataSaver::isSavedToTracker(XDataModel &model, TrackerType type)
{
    SpaceVector posUL;
    SpaceVector posUR;
    SpaceVector posLL;

    computeParameters(model, type, posUL, posUR, posLL);

    if(dataSaved)
    {
        return (posUL == savedUL) && (posUR == savedUR) && (posLL == savedLL);
    }
    else
    {
        return false;
    }
}

bool XDataSaver::saveToTracker(
    XDataModel &model, TrackerType type,
    eyetracker_info::pointer eyetracker,
    MainloopThread& mainloop)

{
    SpaceVector posUL;
    SpaceVector posUR;
    SpaceVector posLL;

    computeParameters(model, type, posUL, posUR, posLL);

    factory_info fi(*eyetracker);
    eyetracker::pointer tracker = create_eyetracker(fi, mainloop.internalMainloop());
    Unlocker::unlock(tracker);

    point_3d ul(posUL.x, posUL.y, posUL.z);
    point_3d ur(posUR.x, posUR.y, posUR.z);
    point_3d ll(posLL.x, posLL.y, posLL.z);

    x_configuration configToSet;
    configToSet.upper_left = ul;
    configToSet.upper_right = ur;
    configToSet.lower_left = ll;

    tracker->set_x_configuration(configToSet);

    dataSaved = true;
    savedUL = posUL;
    savedUR = posUR;
    savedLL = posLL;
    return true;
}

void XDataSaver::computeParameters(XDataModel& m,  TrackerType type,
                                   SpaceVector& posUL, SpaceVector& posUR, SpaceVector& posLL)
{
    XDataModelUnitAdapter model(m);
    SpaceVector posFootPivot;
    double distFootHeight;
    double distFootLength;

    if(type == X120)
    {
        posFootPivot.x = 0.0;
        posFootPivot.y = -30.0;
        posFootPivot.z = -130.0;

        distFootHeight = 22.0;
        distFootLength = 8.0;
    }
    else if (type == TX300)
    {
        posFootPivot.x = 0.0;
        posFootPivot.y = -51.1;
        posFootPivot.z = -87.4;

        distFootHeight = 0.0;
        distFootLength = 0.0;

        if(model.getUseTMode())
        {
            // Hard coded parameters from the TX300 merge file
            posLL.x = -256.9;
            posLL.y = 36.24;
            posLL.z = 1.13;

            posUL.x = -256.9;
            posUL.y = 304.94;
            posUL.z = 110.07;

            posUR.x = 256.9;
            posUR.y = 304.94;
            posUR.z = 110.07;

            return;
        }
    }
    else if (type == ISFM)
    {
        posFootPivot.x = 0.0;
        posFootPivot.y = -26.65;
        posFootPivot.z = -12.556;

        distFootHeight = 0.0;
        distFootLength = 0.0;
    }
    else
    {
        posLL.x = 0.0;
        posLL.y = 0.0;
        posLL.z = 0.0;

        posUL.x = 0.0;
        posUL.y = 0.0;
        posUL.z = 0.0;

        posUR.x = 0.0;
        posUR.y = 0.0;
        posUR.z = 0.0;

        return;
    }

    SpaceVector origin;
    SpaceVector ex(1.0, 0.0, 0.0);
    SpaceVector ey(0.0, 1.0, 0.0);
    SpaceVector ez(0.0, 0.0, 1.0);


    Matrix<double> rotPlane(3,3);
    rotPlane.Make_Rotation_Matrix(deg_to_rad(model.getPlaneAngle()), 0,0);

    Matrix<double> rotTracker(3,3);
    rotTracker.Make_Rotation_Matrix(deg_to_rad(-model.getElevation()),
        (model.getUseTrackerPitch() ? deg_to_rad(model.getTrackerPitch()) : 0.0), 0.0);

    // define plane coordinates relative midpoint of plane lower edge
    posLL = origin - ex * (model.getPlaneDimWidth() * 0.5);
    posUL = posLL + ey * model.getPlaneDimHeight();
    posUR = posUL + ex * model.getPlaneDimWidth();

    // rotate upper corners with plane tilt angle
    posUL = rotPlane * posUL;
    posUR = rotPlane * posUR;

    // move in x direction
    if(model.getUseSideOffset())
    {
            posLL = posLL + ex * model.getSideOffset();
            posUL = posUL + ex * model.getSideOffset();
            posUR = posUR + ex * model.getSideOffset();
    }

    // move in y direction
    double vertDist = model.getPlaneHeight() - distFootHeight;
    posLL = posLL + ey * vertDist;
    posUL = posUL + ey * vertDist;
    posUR = posUR + ey * vertDist;

    // move in z direction
    double horizDist = model.getPlaneDist() + distFootLength;
    posLL = posLL - ez * horizDist;
    posUL = posUL - ez * horizDist;
    posUR = posUR - ez * horizDist;

    // rotate around tracker pivot
    posLL = rotTracker * posLL;
    posUL = rotTracker * posUL;
    posUR = rotTracker * posUR;

    // move from pivot to eyetracker origin
    posLL = posLL + posFootPivot;
    posUL = posUL + posFootPivot;
    posUR = posUR + posFootPivot;

}
