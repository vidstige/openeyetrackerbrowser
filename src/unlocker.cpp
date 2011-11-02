#include "unlocker.h"
#include <tobii/sdk/cpp/tracking/eyetracker.hpp>
#include <tobii/sdk/cpp/tracking/types.hpp>
#include <tobii/sdk/cpp/eyetracker-exception.hpp>

#include <QDebug>

using namespace tobii::sdk::cpp;
using namespace tobii::sdk::cpp::tracking;

Unlocker::Unlocker()
{
}


bool Unlocker::unlock(eyetracker::pointer tracker)
{
    return true;
}
