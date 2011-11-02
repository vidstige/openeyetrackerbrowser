#-------------------------------------------------
#
# Project created by QtCreator 2011-05-03T13:58:08
#
#-------------------------------------------------

QT       += core gui

TARGET = EyetrackerBrowser
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    ListviewDelegate.cpp \
    MainloopThread.cpp \
    EyetrackerBrowser.cpp \
    EyetrackerBrowserEventArgs.cpp \
    UpgradeDialog.cpp \
    UpgradeManager.cpp \
    XConfigDialogTX300.cpp \
    SetNameDialog.cpp \
    XDataModel.cpp \
    BackgroundWorker.cpp \
    TrackerProperties.cpp \
    XDataSaver.cpp \
    XDataFile.cpp \
    XDataModelUnitAdapter.cpp \
    DiagnosticsDialog.cpp \
    EyeTrackerBrowserApplication.cpp \
    unlocker.cpp \
    singletracker.cpp \
    BusyIndicator.cpp \
    WaitForTrackerDialog.cpp

HEADERS  += mainwindow.h \
    ListviewDelegate.h \
    MainloopThread.h \
    EyetrackerBrowser.h \
    EyetrackerBrowserEventArgs.h \
    UpgradeDialog.h \
    UpgradeManager.h \
    XConfigDialogTX300.h \
    SetNameDialog.h \
    XDataModel.h \
    BackgroundWorker.h \
    TrackerProperties.h \
    XDataSaver.h \
    MathTypes.h \
    XDataFile.h \
    XDataModelUnitAdapter.h \
    DiagnosticsDialog.h \
    AppVersion.hpp \
    EyeTrackerBrowserApplication.h \
    unlocker.h \
    singletracker.h \
    BusyIndicator.h \
    WaitForTrackerDialog.h

FORMS    += mainwindow.ui \
    UpgradeDialog.ui \
    XConfigDialogTX300.ui \
    SetNameDialog.ui \
    DiagnosticsDialog.ui \
    WaitForTrackerDialog.ui

RESOURCES += \
    XConf.qrc

unix:!macx {
    LIBS += -ltobiisdk -L/usr/lib
}

win32 {

CONFIG(release, debug|release) {
    LIBS += $$quote($$(BOOST_ROOT))/boost_1_41/lib/libboost_thread-vc90-mt-1_41.lib
    LIBS += $$quote($$(BOOST_ROOT))/boost_1_41/lib/libboost_date_time-vc90-mt-1_41.lib
}

CONFIG(debug, debug|release) {
    LIBS += $$quote($$(BOOST_ROOT))/boost_1_41/lib/libboost_thread-vc90-mt-gd-1_41.lib
    LIBS += $$quote($$(BOOST_ROOT))/boost_1_41/lib/libboost_date_time-vc90-mt-gd-1_41.lib
}

}

win32:INCLUDEPATH += $$quote($$(BOOST_ROOT))/boost_1_41
win32:INCLUDEPATH += ../Win32/C++/includes
win32:INCLUDEPATH += Win32/C++/includes

win32:LIBS += -L"$$_PRO_FILE_PWD_/../Win32/C++/binaries/" -ltobiisdk

OTHER_FILES +=
win32:RC_FILE = windows_icon.rc

OTHER_FILES += \
    windows_icon.rc

macx:INCLUDEPATH += /opt/local/include
macx:QMAKE_LFLAGS += -F../
macx:LIBS += -framework TobiiSDK
macx:LIBS += /opt/local/lib/libboost_thread-mt.a /opt/local/lib/libboost_date_time-mt.a
