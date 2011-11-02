#ifndef DIAGNOSTICSDIALOG_H
#define DIAGNOSTICSDIALOG_H

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


#include <QDialog>
#include <QSharedPointer>
#include <QString>
#include "BackgroundWorker.h"
#include "EyetrackerBrowserEventArgs.h"

namespace Ui {
    class DiagnosticsDialog;
}

class DiagnosticsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DiagnosticsDialog(BackgroundWorker& backgroundWorker,
                               QSharedPointer<EyetrackerBrowserEventArgs> args,
                               QWidget *parent = 0);
    ~DiagnosticsDialog();

signals:
    void startGetDiagnostics(QSharedPointer<EyetrackerBrowserEventArgs>, bool, QString);

public slots:
    void cancelButtonClicked();
    void continueButtonClicked();
    void diagnosticsDataSaved(bool result);
    void debugMovieCaptureProgress(int current, int total);

private:
    Ui::DiagnosticsDialog *ui;
    BackgroundWorker& worker;
    QSharedPointer<EyetrackerBrowserEventArgs> browserData;
};

#endif // DIAGNOSTICSDIALOG_H
