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

#include "DiagnosticsDialog.h"
#include "ui_DiagnosticsDialog.h"
#include <QMessageBox>
#include <QFileDialog>

DiagnosticsDialog::DiagnosticsDialog(BackgroundWorker& backgroundWorker,
                                     QSharedPointer<EyetrackerBrowserEventArgs> args,
                                     QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiagnosticsDialog),
    worker(backgroundWorker),
    browserData(args)
{
    ui->setupUi(this);
    ui->progressLabel->setVisible(false);

    // Connect Buttons
    connect(ui->continueButton, SIGNAL(clicked()), this, SLOT(continueButtonClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));

    // Connect Backgroundworker
    connect(&worker, SIGNAL(debugMovieCaptureProgress(int,int)), this, SLOT(debugMovieCaptureProgress(int,int)), Qt::QueuedConnection);
    connect(&worker, SIGNAL(diagnosticsDataSaved(bool)), this, SLOT(diagnosticsDataSaved(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(startGetDiagnostics(QSharedPointer<EyetrackerBrowserEventArgs>,bool,QString)),
            &worker, SLOT(getDiagnostics(QSharedPointer<EyetrackerBrowserEventArgs>,bool,QString)), Qt::QueuedConnection);
}

DiagnosticsDialog::~DiagnosticsDialog()
{
    delete ui;
}

void DiagnosticsDialog::cancelButtonClicked()
{
    reject();
}

void DiagnosticsDialog::continueButtonClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Diagnostics File", "", "Diagnostics File (*.diag)");
    if(!fileName.isNull())
    {
        if(!fileName.endsWith(".diag"))
            fileName.append(".diag");

        ui->continueButton->setEnabled(false);
        ui->cancelButton->setEnabled(false);
        emit startGetDiagnostics(browserData, ui->includeMovieCheckBox->isChecked(), fileName);
    }
}

void DiagnosticsDialog::diagnosticsDataSaved(bool result)
{
    if(result)
    {
        QMessageBox box(this);
        box.setIcon(QMessageBox::Information);
        box.setText("Diagnostics Data Saved!");
        box.setWindowTitle("");
        box.exec();
    }
    else
    {
        QMessageBox box(this);
        box.setIcon(QMessageBox::Warning);
        box.setText("Failed to Save Diagnostics Data!");
        box.setWindowTitle("Error");
        box.exec();
    }

    ui->continueButton->setEnabled(true);
    ui->cancelButton->setEnabled(true);

    accept();
}

void DiagnosticsDialog::debugMovieCaptureProgress(int current, int total)
{
    QString message = "Capturing Movie " + QString::number(current) + "/" + QString::number(total);
    ui->progressLabel->setText(message);
    ui->progressLabel->setVisible(true);
}
