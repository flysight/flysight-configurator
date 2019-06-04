/***************************************************************************
**                                                                        **
**  FlySight Configurator                                                 **
**  Copyright 2018 Michael Cooper                                         **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see <http://www.gnu.org/licenses/>. **
**                                                                        **
****************************************************************************
**  Contact: Michael Cooper                                               **
**  Website: http://flysight.ca/                                          **
****************************************************************************/

#include "speechform.h"
#include "ui_speechform.h"

#include <QComboBox>
#include <QSpinBox>

#include "configuration.h"

#define MAX_SPEECH 3

SpeechForm::SpeechForm(QWidget *parent) :
    ConfigurationPage(parent),
    ui(new Ui::SpeechForm)
{
    ui->setupUi(this);

    ui->rateEdit->setText(QString::number(0));

    for (int i = 0; i <= 8; ++i)
    {
        ui->volumeComboBox->addItem(QString("%1%").arg(i / 8. * 100));
    }
    ui->volumeComboBox->setCurrentIndex(8);

    // Add headers
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(
                QStringList() << tr("Mode") << tr("Units") << tr("Decimal places"));

    // Connect add/remove buttons
    connect(ui->addButton, SIGNAL(clicked(bool)),
            this, SLOT(add()));
    connect(ui->removeButton, SIGNAL(clicked(bool)),
            this, SLOT(remove()));

    // Update controls when selection changes
    connect(ui->tableWidget, SIGNAL(itemSelectionChanged()),
            this, SLOT(updateControls()));

    // Initial update
    updateControls();
}

SpeechForm::~SpeechForm()
{
    delete ui;
}

int SpeechForm::add()
{
    int i = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(i);

    QComboBox *combo = new QComboBox;

    combo->addItem("Horizontal speed", Configuration::HorizontalSpeed);
    combo->addItem("Vertical speed", Configuration::VerticalSpeed);
    combo->addItem("Glide ratio", Configuration::GlideRatio);
    combo->addItem("Inverse glide ratio", Configuration::InverseGlideRatio);
    combo->addItem("Total speed", Configuration::TotalSpeed);
    combo->addItem("Altitude above ground", Configuration::Altitude);
    combo->addItem("Dive angle", Configuration::DiveAngle);
    combo->setCurrentIndex(2);

    ui->tableWidget->setCellWidget(i, 0, combo);

    combo = new QComboBox;

    combo->addItem("km/h");
    combo->addItem("mph");
    combo->setCurrentIndex(1);

    ui->tableWidget->setCellWidget(i, 1, combo);

    QSpinBox *spin = new QSpinBox;

    spin->setRange(0, 2);
    spin->setValue(0);

    ui->tableWidget->setCellWidget(i, 2, spin);

    updateControls();

    return i;
}

void SpeechForm::remove()
{
    QModelIndexList list;
    while ((list = ui->tableWidget->selectionModel()->selectedIndexes()).size())
    {
        ui->tableWidget->model()->removeRow(list.first().row());
    }

    updateControls();
}

void SpeechForm::updateControls()
{
    QItemSelectionModel *select = ui->tableWidget->selectionModel();
    ui->removeButton->setEnabled(select->hasSelection());
    ui->addButton->setEnabled(ui->tableWidget->rowCount() < MAX_SPEECH);
}

void SpeechForm::setConfiguration(
        const Configuration &configuration)
{
    ui->rateEdit->setText(
                QString::number(configuration.speechRate));
    ui->volumeComboBox->setCurrentIndex(configuration.speechVolume);

    // Remove all speech
    while (ui->tableWidget->rowCount() > 0)
    {
        ui->tableWidget->removeRow(0);
    }

    // Add speech
    foreach (Configuration::Speech speech, configuration.speeches)
    {
        if (ui->tableWidget->rowCount() >= MAX_SPEECH) break;

        int i = add();

        QComboBox *combo = (QComboBox*) ui->tableWidget->cellWidget(i, 0);
        int index = combo->findData(speech.mode);
        combo->setCurrentIndex(index);

        combo = (QComboBox*) ui->tableWidget->cellWidget(i, 1);
        combo->setCurrentIndex(speech.units);

        QSpinBox *spin = (QSpinBox *) ui->tableWidget->cellWidget(i, 2);
        spin->setValue(speech.decimals);
    }
}

void SpeechForm::updateConfiguration(
        Configuration &configuration,
        UpdateOptions options) const
{
    if (!(options & Values)) return;

    configuration.speechRate = ui->rateEdit->text().toInt();
    configuration.speechVolume = ui->volumeComboBox->currentIndex();

    // Clear speech in configuration
    configuration.speeches.clear();

    // Add alarms from interface
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        Configuration::Speech speech;

        QComboBox *combo = (QComboBox*) ui->tableWidget->cellWidget(i, 0);
        speech.mode = (Configuration::Mode) combo->itemData(combo->currentIndex()).toInt();

        combo = (QComboBox*) ui->tableWidget->cellWidget(i, 1);
        speech.units = (Configuration::Units) combo->currentIndex();

        QSpinBox *spin = (QSpinBox*) ui->tableWidget->cellWidget(i, 2);
        speech.decimals = spin->value();

        configuration.speeches.push_back(speech);
    }
}
