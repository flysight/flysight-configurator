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

#include "configuration.h"

SpeechForm::SpeechForm(QWidget *parent) :
    ConfigurationPage(parent),
    ui(new Ui::SpeechForm)
{
    ui->setupUi(this);

    ui->modeComboBox->addItem("Horizontal speed");
    ui->modeComboBox->addItem("Vertical speed");
    ui->modeComboBox->addItem("Glide ratio");
    ui->modeComboBox->addItem("Inverse glide ratio");
    ui->modeComboBox->addItem("Total speed");

    ui->unitsComboBox->addItem("km/h");
    ui->unitsComboBox->addItem("mph");

    for (int i = 0; i <= 8; ++i)
    {
        ui->volumeComboBox->addItem(QString("%1%").arg(i / 8. * 100));
    }
}

SpeechForm::~SpeechForm()
{
    delete ui;
}

void SpeechForm::setConfiguration(
        const Configuration &configuration)
{
    ui->modeComboBox->setCurrentIndex(configuration.speechMode);
    ui->unitsComboBox->setCurrentIndex(configuration.speechUnits);
    ui->rateEdit->setText(
                QString::number(configuration.speechRate));
    ui->decimalsSpinBox->setValue(configuration.speechDecimals);
    ui->volumeComboBox->setCurrentIndex(configuration.speechVolume);
}

void SpeechForm::updateConfiguration(
        Configuration &configuration,
        UpdateOptions options) const
{
    if (!(options & Values)) return;

    configuration.speechMode = (Configuration::Mode) ui->modeComboBox->currentIndex();
    configuration.speechUnits = (Configuration::Units) ui->unitsComboBox->currentIndex();
    configuration.speechRate = ui->rateEdit->text().toInt();
    configuration.speechDecimals = ui->decimalsSpinBox->value();
    configuration.speechVolume = ui->volumeComboBox->currentIndex();
}
