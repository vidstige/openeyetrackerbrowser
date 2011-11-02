#include "XConfigDialogTX300.h"
#include "ui_XConfigDialogTX300.h"
#include "XDataFile.h"

#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>

XConfigDialogTX300::XConfigDialogTX300(
        eyetracker_info::pointer info,
        MainloopThread& loop,
        QWidget *parent) :
    _info(info),
    QDialog(parent),
    ui(new Ui::XConfigDialogTX300),
    mainloop(loop)
{
    ui->setupUi(this);

    QString modelString = QString::fromStdString(_info->get_model());
    QString productId = QString::fromStdString(_info->get_product_id());
    this->setWindowTitle("X Configuration Tool [ " + productId + " ]");

    if(modelString == "Tobii TX300")
    {
        trackerType = XDataSaver::TX300;
        ui->mainPicture->setPixmap(QPixmap(":/XConf/X Main TX300.png"));
        ui->offsetPicture->setPixmap(QPixmap(":/XConf/X sideoff TX300.png"));
        ui->rotationPicture->setPixmap(QPixmap(":/XConf/X pitch TX300.png"));
    }
    else if(modelString == "Tobii X120" || modelString == "Tobii X60")
    {
        trackerType = XDataSaver::X120;
        ui->mainPicture->setPixmap(QPixmap(":/XConf/X Main.png"));
        ui->offsetPicture->setPixmap(QPixmap(":/XConf/X sideoff.png"));
        ui->rotationPicture->setPixmap(QPixmap(":/XConf/X pitch.png"));
    }

    else if(modelString == "Tobii-IS")
    {
        trackerType = XDataSaver::ISFM;
        ui->mainPicture->setPixmap(QPixmap(":/XConf/X Main ISFM.png"));
        ui->offsetPicture->setPixmap(QPixmap(":/XConf/X sideoff ISFM.png"));
        ui->rotationPicture->setPixmap(QPixmap(":/XConf/X pitch ISFM.png"));
    }

    connect(&model, SIGNAL(modelChanged()), this, SLOT(updateUserInterface()));

    connect(ui->cmRadioButton, SIGNAL(toggled(bool)), this, SLOT(lengthUnitToggled(bool)));

    connect(ui->elevationSpinBox,SIGNAL(valueChanged(double)),&model,SLOT(setElevation(double)));
    connect(ui->elevationSpinBox_2,SIGNAL(valueChanged(double)),&model,SLOT(setElevation(double)));
    connect(ui->planeHeightSpinBox, SIGNAL(valueChanged(double)),&model,SLOT(setPlaneHeight(double)));
    connect(ui->planeHeightSpinBox_2, SIGNAL(valueChanged(double)),&model,SLOT(setPlaneHeight(double)));
    connect(ui->planeDistSpinBox, SIGNAL(valueChanged(double)),&model,SLOT(setPlaneDist(double)));
    connect(ui->planeAngleSpinBox, SIGNAL(valueChanged(double)),&model,SLOT(setPlaneAngle(double)));
    connect(ui->planeDimWidthSpinBox, SIGNAL(valueChanged(double)),&model,SLOT(setPlaneDimWidth(double)));
    connect(ui->planeDimHeightSpinBox, SIGNAL(valueChanged(double)),&model,SLOT(setPlaneDimHeight(double)));

    connect(ui->usePitchCheckBox, SIGNAL(toggled(bool)),&model,SLOT(setUseTrackerPitch(bool)));
    connect(ui->useSideOffsetCheckBox, SIGNAL(toggled(bool)),&model,SLOT(setUseSideOffset(bool)));

    connect(ui->pitchSpinBox, SIGNAL(valueChanged(double)),&model,SLOT(setTrackerPitch(double)));
    connect(ui->sideOffsetSpinBox, SIGNAL(valueChanged(double)),&model,SLOT(setSideOffset(double)));
    connect(ui->useTModeCheckBox, SIGNAL(toggled(bool)), &model, SLOT(setUseTMode(bool)));

    connect(ui->saveButton,SIGNAL(clicked()), this, SLOT(saveToTracker()));
    connect(ui->saveToFileButton, SIGNAL(clicked()), this, SLOT(saveToFile()));
    connect(ui->loadFromFileButton, SIGNAL(clicked()), this, SLOT(loadFromFile()));

    updateUserInterface();
}

XConfigDialogTX300::~XConfigDialogTX300()
{
    delete ui;
}

void XConfigDialogTX300::lengthUnitToggled(bool)
{
    // Ignore value
    if(ui->cmRadioButton->isChecked())
    {
        model.setLengthUnit(XDataModel::CM);
    }
    else
    {
        model.setLengthUnit(XDataModel::INCH);
    }
}

void XConfigDialogTX300::updateUserInterface()
{
    XDataModel::LengthUnit unit = model.getLengthUnit();

    bool inXMode = !model.getUseTMode();

    ui->cmRadioButton->setChecked(unit == XDataModel::CM);
    ui->inchRadioButton->setChecked(unit == XDataModel::INCH);
    QString lengthText = unit == XDataModel::CM ? "[cm]" : "[inch]";

    ui->elevationSpinBox->setValue(model.getElevation());
    ui->elevationSpinBox_2->setValue(model.getElevation());
    ui->planeDistSpinBox->setValue(model.getPlaneDist());
    ui->planeHeightSpinBox->setValue(model.getPlaneHeight());
    ui->planeHeightSpinBox_2->setValue(model.getPlaneHeight());
    ui->planeAngleSpinBox->setValue(model.getPlaneAngle());
    ui->planeDimWidthSpinBox->setValue(model.getPlaneDimWidth());
    ui->planeDimHeightSpinBox->setValue(model.getPlaneDimHeight());

    ui->usePitchCheckBox->setChecked(model.getUseTrackerPitch());
    ui->useSideOffsetCheckBox->setChecked(model.getUseSideOffset());
    ui->useTModeCheckBox->setChecked(model.getUseTMode());

    ui->pitchSpinBox->setValue(model.getTrackerPitch());
    ui->sideOffsetSpinBox->setValue(model.getSideOffset());

    ui->planeDistLabel->setText(lengthText);
    ui->planeHeightLabel->setText(lengthText);
    ui->planeHeightLabel_2->setText(lengthText);
    ui->sideOffsetLabel->setText(lengthText);

    // Set enabled states

    ui->mainPicture->setEnabled(inXMode);

    ui->rotationPicture->setEnabled(ui->usePitchCheckBox->isChecked() && inXMode);
    ui->pitchSpinBox->setEnabled(ui->usePitchCheckBox->isChecked() && inXMode);

    ui->offsetPicture->setEnabled(ui->useSideOffsetCheckBox->isChecked() && inXMode);
    ui->sideOffsetSpinBox->setEnabled(ui->useSideOffsetCheckBox->isChecked() && inXMode);

    ui->elevationSpinBox->setEnabled(inXMode);
    ui->elevationSpinBox_2->setEnabled(inXMode);
    ui->planeDistSpinBox->setEnabled(inXMode);
    ui->planeHeightSpinBox->setEnabled(inXMode);
    ui->planeHeightSpinBox_2->setEnabled(inXMode);
    ui->planeAngleSpinBox->setEnabled(inXMode);
    ui->planeDimWidthSpinBox->setEnabled(inXMode);
    ui->planeDimHeightSpinBox->setEnabled(inXMode);

    ui->cmRadioButton->setEnabled(inXMode);
    ui->inchRadioButton->setEnabled(inXMode);
    ui->usePitchCheckBox->setEnabled(inXMode);
    ui->useSideOffsetCheckBox->setEnabled(inXMode);

    ui->loadFromFileButton->setEnabled(inXMode);
    ui->saveToFileButton->setEnabled(inXMode);

    // Set widget visibility
    if(trackerType == XDataSaver::TX300)
    {
        // Hide X120/X60 specific widgets
        ui->elevationLabel_2->setVisible(false);
        ui->elevationSpinBox_2->setVisible(false);
        ui->planeHeightLabel_2->setVisible(false);
        ui->planeHeightSpinBox_2->setVisible(false);
    }
    else if(trackerType == XDataSaver::ISFM)
    {
        // use same widgets as TX300
        ui->elevationLabel_2->setVisible(false);
        ui->elevationSpinBox_2->setVisible(false);
        ui->planeHeightLabel_2->setVisible(false);
        ui->planeHeightSpinBox_2->setVisible(false);

        // except the T mode checkbox
        ui->useTModeCheckBox->setVisible(false);
    }
    else
    {
        // hide TX300 specific widgets
        ui->elevationLabel->setVisible(false);
        ui->elevationSpinBox->setVisible(false);
        ui->planeHeightLabel->setVisible(false);
        ui->planeHeightSpinBox->setVisible(false);
        ui->useTModeCheckBox->setVisible(false);
    }
}

void XConfigDialogTX300::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save X Config File", "", "X Config Files (*.xconf)");
    if (!fileName.isNull())
    {
        if (!fileName.endsWith(".xconf"))
            fileName.append(".xconf");

        if (!XDataFile::saveToFile(model, fileName))
        {
            QMessageBox box(this);
            box.setIcon(QMessageBox::Warning);
            box.setText("File could not be saved");
            box.setWindowTitle("");
            box.exec();
        }
    }
}

void XConfigDialogTX300::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open X Config File", "", "X Config Files (*.xconf)");
    if (!fileName.isNull())
    {
        if (XDataFile::readFromFile(model, fileName))
        {
            updateUserInterface();
        }
        else
        {
            QMessageBox box(this);
            box.setIcon(QMessageBox::Warning);
            box.setText("Failed to load x config file!");
            box.setWindowTitle("Error");
            box.exec();
        }
    }
}

void XConfigDialogTX300::saveToTracker()
{
    saver.saveToTracker(model, XDataSaver::TX300, _info, mainloop);

    QMessageBox box(this);
    box.setIcon(QMessageBox::Information);
    box.setText("Parameters successfully transmitted to eye tracker!");
    box.setWindowTitle("");
    box.exec();
}

void XConfigDialogTX300::closeEvent(QCloseEvent *event)
{
    if (!saver.isSavedToTracker(model, XDataSaver::TX300))
    {
        QMessageBox box(this);
        box.setIcon(QMessageBox::Question);
        box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        box.setText("Quit without saving parameters to eye tracker?");
        box.setWindowTitle("");
        int ret = box.exec();
        if(ret == QMessageBox::Cancel)
        {
            event->ignore();
        }
        else
        {
            event->accept();
        }

    }
    else
    {
        event->accept();
    }
}
