#ifndef MAINLOOPTHREAD_H
#define MAINLOOPTHREAD_H

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


#include <QThread>
#include <tobii/sdk/cpp/mainloop.hpp>

class MainloopThread : public QThread
{
    Q_OBJECT
public:
    explicit MainloopThread(QObject *parent = 0);
    virtual ~MainloopThread();

    void quit();

    const tobii::sdk::cpp::mainloop& internalMainloop();

signals:

public slots:

protected:
    virtual void run();

private:
    tobii::sdk::cpp::mainloop mainloop;
};

#endif // MAINLOOPTHREAD_H
