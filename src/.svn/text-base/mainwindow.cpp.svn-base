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

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QClipboard>
#include <QFont>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ListviewDelegate.h"
#include "UpgradeDialog.h"
#include "XConfigDialogTX300.h"
#include "SetNameDialog.h"
#include "DiagnosticsDialog.h"

#include <boost/bind.hpp>
#include <tobii/sdk/cpp/upgrade/upgrade.hpp>


using namespace boost;
using namespace tobii::sdk::cpp;
using namespace tobii::sdk::cpp::discovery;
using namespace tobii::sdk::cpp::upgrade;

MainWindow::MainWindow(MainloopThread &mainloopThread, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    worker(mainloopThread),
    m_mainloopThread(mainloopThread)
{
    ui->setupUi(this);

    ui->oldFirmwareLabel->setVisible(false);

    // Register custom type used in Eyetrackerbrowser signal
    qRegisterMetaType<QSharedPointer<EyetrackerBrowserEventArgs> >("QSharedPointer<EyetrackerBrowserEventArgs>");
    qRegisterMetaType<TrackerProperties>("TrackerProperties");
    qRegisterMetaType<TrackerProperties::IlluminationMode>("TrackerProperties::IlluminationMode");

    m_mainloopThread.start();

    // Create browser and subscribe to events
    browser =
            QSharedPointer<EyetrackerBrowser>(new EyetrackerBrowser(m_mainloopThread.internalMainloop()));

    connect(browser.data(), SIGNAL(browserEvent(QSharedPointer<EyetrackerBrowserEventArgs>)),
        this, SLOT(handleBrowserEventInternal(QSharedPointer<EyetrackerBrowserEventArgs>)), Qt::QueuedConnection);

    // Create a ListviewDelegate for custom drawing
    ListviewDelegate *listdelegate = new ListviewDelegate();
    ui->listView->setItemDelegate(listdelegate);

    // Create and set list view model
    model = new QStandardItemModel();
    ui->listView->setModel(model);

    // Listen for selection changes
    QItemSelectionModel* selectionModel = ui->listView->selectionModel();
    connect(selectionModel, SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(currentItemChanged(QModelIndex,QModelIndex)));

    // Connect buttons and combo boxes
    connect(ui->upgradeButton, SIGNAL(clicked()), this, SLOT(startUpgrade()));
    connect(ui->configButton, SIGNAL(clicked()), this, SLOT(openConfigTool()));
    connect(ui->setNameButton, SIGNAL(clicked()), this, SLOT(openSetNameDialog()));
    connect(ui->frameRateComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(framerateIndexChanged(int)));
    connect(ui->illuminationComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(illuminationIndexChanged(int)));
    connect(ui->copyButton, SIGNAL(clicked()), this, SLOT(copyButtonClicked()));
    connect(ui->diagnosticsButton, SIGNAL(clicked()), this, SLOT(diagnosticsButtonClicked()));

    // Connect background worker
    connect(this, SIGNAL(startResolvingTrackerProperties(QSharedPointer<EyetrackerBrowserEventArgs>)),
            &worker, SLOT(resolveTrackerProperties(QSharedPointer<EyetrackerBrowserEventArgs>)),Qt::QueuedConnection);

    connect(&worker, SIGNAL(trackerPropertiesResolved(TrackerProperties)),
            this, SLOT(trackerPropertiesResolved(TrackerProperties)), Qt::QueuedConnection);

    connect(this, SIGNAL(startSettingFramerate(QSharedPointer<EyetrackerBrowserEventArgs>,float)),
            &worker, SLOT(setFrameRate(QSharedPointer<EyetrackerBrowserEventArgs>,float)), Qt::QueuedConnection);

    connect(this, SIGNAL(startSettingIlluminationMode(QSharedPointer<EyetrackerBrowserEventArgs>,TrackerProperties::IlluminationMode,QString)),
            &worker, SLOT(setIlluminationMode(QSharedPointer<EyetrackerBrowserEventArgs>,TrackerProperties::IlluminationMode,QString)), Qt::QueuedConnection);

    QLabel* versionLabel = new QLabel();
    versionLabel->setText("Tool Version: " + QApplication::instance()->applicationVersion());
    ui->statusBar->addPermanentWidget(versionLabel);

#ifdef Q_OS_MAC

    QFont font = ui->upgradeButton->font();
    font.setPointSize(9);

    ui->upgradeButton->setFont(font);
    ui->configButton->setFont(font);
    ui->setNameButton->setFont(font);
    ui->diagnosticsButton->setFont(font);
    ui->copyButton->setFont(font);

#endif

}

void MainWindow::currentItemChanged(const QModelIndex &current, const QModelIndex &previous)
{
    QString selectedProductId = qvariant_cast<QString>(current.data(ListviewDelegate::ProductIdRole));

    BrowserDataMap::iterator browserDataIt = browserDataMap.find(selectedProductId);
    if(browserDataIt != browserDataMap.end())
    {
        QSharedPointer<EyetrackerBrowserEventArgs> browserData = browserDataIt.value();
        QString firmwareVersion = QString::fromStdString(browserData->info()->get_version());

        bool statusOk = QString::fromStdString(browserData->info()->get_status()) == "ok";

        startAsyncTrackerUpdate(browserData);

        ui->firmwareLabel->setText(firmwareVersion);
        ui->oldFirmwareLabel->setVisible(false);

        ui->hostNameLabel->setText(selectedProductId + ".local : 4455");

        ui->configButton->setEnabled(trackerSupportsXConfig(browserData) && statusOk);
        ui->setNameButton->setEnabled(current.isValid() && statusOk);
        ui->diagnosticsButton->setEnabled(current.isValid() && statusOk);
        ui->upgradeButton->setEnabled(current.isValid());

    }
    else
    {
        ui->firmwareLabel->setText("");
        ui->oldFirmwareLabel->setVisible(false);
        ui->hostNameLabel->setText("");

        ui->configButton->setEnabled(false);
        ui->setNameButton->setEnabled(false);
        ui->diagnosticsButton->setEnabled(false);
        ui->upgradeButton->setEnabled(false);

    }

}

void MainWindow::framerateIndexChanged(int index)
{
    if(index >= 0)
    {
        float framerate = ui->frameRateComboBox->itemData(index).toFloat();
        QSharedPointer<EyetrackerBrowserEventArgs> currentTracker = browserDataFromCurrentSelection();
        if(!currentTracker.isNull())
        {
            emit startSettingFramerate(currentTracker, framerate);
        }
    }
}

void MainWindow::illuminationIndexChanged(int index)
{
    if(index >= 0)
    {
        TrackerProperties::IlluminationMode mode = (TrackerProperties::IlluminationMode) ui->illuminationComboBox->itemData(index).toInt();

        QSharedPointer<EyetrackerBrowserEventArgs> currentTracker = browserDataFromCurrentSelection();
        if(!currentTracker.isNull())
        {
            emit startSettingIlluminationMode(currentTracker, mode, ui->illuminationComboBox->itemText(index));
        }
    }
}

void MainWindow::startAsyncTrackerUpdate(QSharedPointer<EyetrackerBrowserEventArgs> args)
{
    ui->frameRateComboBox->setEnabled(false);
    ui->illuminationComboBox->setEnabled(false);

    emit startResolvingTrackerProperties(args);
}



void MainWindow::trackerPropertiesResolved(TrackerProperties properties)
{
    // If the selected tracker has changed we ignore this resolve
    QSharedPointer<EyetrackerBrowserEventArgs> currentTracker = browserDataFromCurrentSelection();

    // These lines are a fix for when we get the first resolve signal when no item is selected but
    // when the current index has changed
    if(currentTracker.isNull())
    {
        BrowserDataMap::iterator browserDataIt = browserDataMap.find(properties.productId);
        if(browserDataIt != browserDataMap.end())
        {
            currentTracker = browserDataIt.value();
        }
    }


    if(currentTracker.isNull() || properties.productId != QString::fromStdString(currentTracker->info()->get_product_id()))
        return;

    if(properties.unsupportedFirmware)
    {
        ui->oldFirmwareLabel->setVisible(true);
        ui->setNameButton->setEnabled(false);
        ui->configButton->setEnabled(false);
        ui->diagnosticsButton->setEnabled(false);
    }
    else
    {
        ui->oldFirmwareLabel->setVisible(false);
        QString firmwareVersion = QString::fromStdString(currentTracker->info()->get_version());
        ui->firmwareLabel->setText(firmwareVersion);

        ui->setNameButton->setEnabled(true);
        ui->configButton->setEnabled(trackerSupportsXConfig(currentTracker));
        ui->diagnosticsButton->setEnabled(true);

        // Populate framerate combo box
        ui->frameRateComboBox->blockSignals(true);
        ui->frameRateComboBox->clear();
        ui->frameRateComboBox->setEnabled(true);

        float f;
        foreach(f, properties.framerates)
            ui->frameRateComboBox->addItem(QString::number(f),f);

        int selectedIndex = properties.framerates.indexOf(properties.currentFramerate);
        if(selectedIndex >= 0)
            ui->frameRateComboBox->setCurrentIndex(selectedIndex);
        ui->frameRateComboBox->blockSignals(false);

        // Populate illumination combo box
        ui->illuminationComboBox->blockSignals(true);
        ui->illuminationComboBox->clear();
        if(properties.hasLowblink)
        {
            ui->illuminationComboBox->addItem("Default", TrackerProperties::LowBlinkDisabled);
            ui->illuminationComboBox->addItem("Low Blink Mode", TrackerProperties::LowBlinkEnabled);
            ui->illuminationComboBox->setCurrentIndex(properties.lowBlinkEnabled ? 1 : 0);
            ui->illuminationComboBox->setEnabled(true);
        }
        else if(properties.currentIlluminationMode != "" && properties.illuminationModes.size() > 0)
        {
            QString m;
            foreach(m, properties.illuminationModes)
                ui->illuminationComboBox->addItem(m, TrackerProperties::Other);

            int ix = properties.illuminationModes.indexOf(properties.currentIlluminationMode);
            if(ix >= 0)
                ui->illuminationComboBox->setCurrentIndex(ix);
            ui->illuminationComboBox->setEnabled(true);
        }

        ui->illuminationComboBox->blockSignals(false);
    }
}

void MainWindow::copyButtonClicked()
{
    QSharedPointer<EyetrackerBrowserEventArgs> browserData = browserDataFromCurrentSelection();
    if(!browserData.isNull())
    {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(QString::fromStdString(browserData->info()->get_product_id()) + ".local.");
    }
}

void MainWindow::diagnosticsButtonClicked()
{
    QSharedPointer<EyetrackerBrowserEventArgs> browserData = browserDataFromCurrentSelection();
    if(!browserData.isNull())
    {
        DiagnosticsDialog dialog(worker, browserData);
        dialog.setParent(this, Qt::Dialog);
        dialog.exec();
    }
}

void MainWindow::startUpgrade()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Select Upgrade Package","", "Tobii Upgrade Package (*.tobiipkg)");

    if(!fileName.isNull())
    {
        QSharedPointer<EyetrackerBrowserEventArgs> browserData = browserDataFromCurrentSelection();

        if(!browserData.isNull())
        {
            QFile file(fileName);
            if(file.open(QIODevice::ReadOnly))
            {
                QByteArray rawData = file.readAll();
                upgrade_package package((const boost::uint8_t*)rawData.constData(), rawData.length());


                if(!checkUpgradePackageCompatibility(package, *(browserData->info())))
                    return;

                UpgradeDialog dialog(m_mainloopThread);

                dialog.startUpgrade(package, *(browserData->info()));
                dialog.setParent(this, Qt::Dialog);
                dialog.exec();
            }
        }
    }
}

bool MainWindow::checkUpgradePackageCompatibility(const tobii::sdk::cpp::upgrade::upgrade_package &upgradePackage,
                                                  const tobii::sdk::cpp::discovery::eyetracker_info &etInfo)
{
    uint error = 0;
    bool compatible =
            upgrade_package_is_compatible_with_device(
                m_mainloopThread.internalMainloop(),
                upgradePackage,
                etInfo, error);

    if(!compatible)
    {
       QString text;

       switch(error)
       {
            case 46:
                text = "The selected eye tracker has a more recent firmware. Downgrade is not possible.";
                break;
            default:
                text = "This upgrade package is not compatible with the selected eye tracker.";
                break;
       }

       QMessageBox box(this);
       box.setIcon(QMessageBox::Information);
       box.setText(text);
       box.setWindowTitle("Upgrade Failed");
       box.exec();
    }

    return compatible;
}

bool MainWindow::trackerSupportsXConfig(QSharedPointer<EyetrackerBrowserEventArgs> args)
{
    QString model = QString::fromStdString(args->info()->get_model());
    return (model == "Tobii TX300" || model == "Tobii X120" || model == "Tobii X60" || model == "Tobii-IS");
}

void MainWindow::openConfigTool()
{
    // Find out which dialog to use
    QSharedPointer<EyetrackerBrowserEventArgs> browserData = browserDataFromCurrentSelection();

    if(!browserData.isNull())
    {
        XConfigDialogTX300 toolDialog(browserData->info(), m_mainloopThread);
        toolDialog.setParent(this, Qt::Dialog);
        toolDialog.exec();
    }
}

void MainWindow::openSetNameDialog()
{
    QSharedPointer<EyetrackerBrowserEventArgs> browserData = browserDataFromCurrentSelection();

    if(!browserData.isNull())
    {
        SetNameDialog dialog(browserData, m_mainloopThread);
        dialog.setParent(this, Qt::Dialog);
        dialog.exec();
    }
}


void MainWindow::handleBrowserEventInternal(QSharedPointer<EyetrackerBrowserEventArgs> args)
{
    QString productId = QString::fromStdString(args->info()->get_product_id());

    if(args->type() == eyetracker_browser::TRACKER_FOUND)
    {
        QStandardItem *item = new QStandardItem();

        QPixmap icon = iconFromBrowserEventArgs(args);
        QString header = headerTextFromBrowserEventArgs(args);
        QString subHeader = subHeaderTextFromBrowserEventArgs(args);

        item->setData(header, ListviewDelegate::headerTextRole);
        item->setData(subHeader, ListviewDelegate::subHeaderTextrole);
        item->setData(icon, ListviewDelegate::IconRole);
        item->setData(productId, ListviewDelegate::ProductIdRole);

        listViewItemMap.insert(productId, item);
        browserDataMap.insert(productId, args);

        model->appendRow(item);
    }
    else if(args->type() == eyetracker_browser::TRACKER_REMOVED)
    {
        browserDataMap.remove(productId);
        QMap<QString, QStandardItem*>::const_iterator it =  listViewItemMap.find(productId);
        if(it != listViewItemMap.end())
        {
            QStandardItem* itemToRemove = it.value();
            QModelIndex index = model->indexFromItem(itemToRemove);
            model->removeRow(index.row());
        }
    }
    else if(args->type() == eyetracker_browser::TRACKER_UPDATED)
    {
        browserDataMap[productId] = args;
        QMap<QString, QStandardItem*>::const_iterator it =  listViewItemMap.find(productId);
        if(it != listViewItemMap.end())
        {
            QStandardItem* itemToUpdate = it.value();

            QPixmap icon = iconFromBrowserEventArgs(args);
            QString header = headerTextFromBrowserEventArgs(args);
            QString subHeader = subHeaderTextFromBrowserEventArgs(args);

            itemToUpdate->setData(header, ListviewDelegate::headerTextRole);
            itemToUpdate->setData(subHeader, ListviewDelegate::subHeaderTextrole);
            itemToUpdate->setData(icon, ListviewDelegate::IconRole);

            // If the update is for the selected tracker we update the tracker properties
            QModelIndexList selectionList = ui->listView->selectionModel()->selectedRows();
            if(selectionList.size() > 0)
            {
                const QModelIndex& selectedIndex = selectionList[0];
                QString selectedProductId = qvariant_cast<QString>(selectedIndex.data(ListviewDelegate::ProductIdRole));
                if(selectedProductId == productId)
                {
                    startAsyncTrackerUpdate(args);
                }
            }

        }
    }
}

QSharedPointer<EyetrackerBrowserEventArgs> MainWindow::browserDataFromCurrentSelection()
{
    QModelIndexList selectionList = ui->listView->selectionModel()->selectedRows();
    if(selectionList.size() > 0)
    {
        const QModelIndex& selectedIndex = selectionList[0];
        QString productIdToUpgrade = qvariant_cast<QString>(selectedIndex.data(ListviewDelegate::ProductIdRole));

        BrowserDataMap::iterator browserDataIt = browserDataMap.find(productIdToUpgrade);
        if(browserDataIt != browserDataMap.end())
        {
            return browserDataIt.value();
        }
    }

    return QSharedPointer<EyetrackerBrowserEventArgs>();
}

QPixmap MainWindow::iconFromBrowserEventArgs(QSharedPointer<EyetrackerBrowserEventArgs> args)
{
    // Create empty pixmap
    QPixmap emptyIcon(4, 64);
    emptyIcon.fill(QColor::fromRgb(255,255,255));
    return emptyIcon;
}


QString MainWindow::headerTextFromBrowserEventArgs(QSharedPointer<EyetrackerBrowserEventArgs> args)
{
    if(args->info()->get_given_name() != "")
        return QString::fromStdString(args->info()->get_given_name());
    return QString::fromStdString(args->info()->get_product_id());
}

QString MainWindow::subHeaderTextFromBrowserEventArgs(QSharedPointer<EyetrackerBrowserEventArgs> args)
{
    if(args->info()->get_status() == "ok")
    {
        QString name = QString::fromStdString(args->info()->get_given_name());

        if(name == "")
        {
            return QString::fromStdString(args->info()->get_model());
        }
        else
        {
            return QString::fromStdString(args->info()->get_product_id()) + " (" + QString::fromStdString(args->info()->get_model()) + ")";
        }

    }
    else if(args->info()->get_status() == "upgrading")
    {
        return QString("Upgrading...");
    }
    else if(args->info()->get_status() == "not-working")
    {
        return QString("Eyetracker not working as expected.");
    }

    return QString("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_oldFirmwareLabel_linkActivated(const QString &link)
{

}
