#ifndef XDATAFILE_H
#define XDATAFILE_H

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


#include <QString>
#include "XDataModel.h"

class XDataFile
{
public:
    XDataFile();

    static bool saveToFile(XDataModel& model, QString fileName);

    static bool readFromFile(XDataModel& model, QString fileName);
};

#endif // XDATAFILE_H
