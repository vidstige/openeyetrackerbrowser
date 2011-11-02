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

#include "MainloopThread.h"

using namespace tobii::sdk::cpp;

MainloopThread::MainloopThread(QObject *parent) :
    QThread(parent)
{
}

MainloopThread::~MainloopThread()
{
    quit();
    wait();
}

void MainloopThread::run()
{
    mainloop.run();
}

void MainloopThread::quit()
{
    mainloop.quit();
}

const tobii::sdk::cpp::mainloop& MainloopThread::internalMainloop()
{
    return mainloop;
}
