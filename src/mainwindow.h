#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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


#include <QMainWindow>
#include <QSharedPointer>
#include <QStandardItemModel>
#include <QMap>

#include "MainloopThread.h"
#include "BackgroundWorker.h"
#include "EyetrackerBrowser.h"
#include "EyetrackerBrowserEventArgs.h"
#include "TrackerProperties.h"
#include <tobii/sdk/cpp/discovery/eyetracker-browser.hpp>
#include <tobii/sdk/cpp/discovery/eyetracker-info.hpp>
#include <tobii/sdk/cpp/upgrade/upgrade-package.hpp>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    typedef QMap<QString, QSharedPointer<EyetrackerBrowserEventArgs> > BrowserDataMap;

    explicit MainWindow(MainloopThread &mainloopThread, QWidget *parent = 0);
    ~MainWindow();

signals:
    void startResolvingTrackerProperties(QSharedPointer<EyetrackerBrowserEventArgs>);
    void startSettingFramerate(QSharedPointer<EyetrackerBrowserEventArgs>, float framerate);
    void startSettingIlluminationMode(QSharedPointer<EyetrackerBrowserEventArgs> args,
                                      TrackerProperties::IlluminationMode mode, QString custom);

public slots:
    void handleBrowserEventInternal(QSharedPointer<EyetrackerBrowserEventArgs> args);
    void startUpgrade();
    void openConfigTool();
    void openSetNameDialog();
    void copyButtonClicked();
    void diagnosticsButtonClicked();
    void currentItemChanged (const QModelIndex & current, const QModelIndex & previous);
    bool checkUpgradePackageCompatibility(const tobii::sdk::cpp::upgrade::upgrade_package &upgradePackage,
                                          const tobii::sdk::cpp::discovery::eyetracker_info &etInfo);
    bool trackerSupportsXConfig(QSharedPointer<EyetrackerBrowserEventArgs> args);

private slots:
    void trackerPropertiesResolved(TrackerProperties properties);
    void framerateIndexChanged(int index);
    void illuminationIndexChanged(int index);

    void on_oldFirmwareLabel_linkActivated(const QString &link);

private:
    QSharedPointer<EyetrackerBrowserEventArgs> browserDataFromCurrentSelection();
    void startAsyncTrackerUpdate(QSharedPointer<EyetrackerBrowserEventArgs> args);

    QPixmap iconFromBrowserEventArgs(QSharedPointer<EyetrackerBrowserEventArgs> args);
    QString headerTextFromBrowserEventArgs(QSharedPointer<EyetrackerBrowserEventArgs> args);
    QString subHeaderTextFromBrowserEventArgs(QSharedPointer<EyetrackerBrowserEventArgs> args);

    Ui::MainWindow *ui;
    MainloopThread &m_mainloopThread;
    BackgroundWorker worker;
    QStandardItemModel* model;
    QSharedPointer<EyetrackerBrowser> browser;
    QMap<QString, QStandardItem*> listViewItemMap;
    BrowserDataMap browserDataMap;
};

#endif // MAINWINDOW_H
