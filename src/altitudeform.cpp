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

#include "altitudeform.h"
#include "ui_altitudeform.h"

#include "configuration.h"

AltitudeForm::AltitudeForm(QWidget *parent) :
    ConfigurationPage(parent),
    ui(new Ui::AltitudeForm)
{
    ui->setupUi(this);

    ui->unitsComboBox->addItem("meters");
    ui->unitsComboBox->addItem("feet");
}

AltitudeForm::~AltitudeForm()
{
    delete ui;
}

void AltitudeForm::setConfiguration(
        const Configuration &configuration)
{
    ui->unitsComboBox->setCurrentIndex(configuration.altitudeUnits);
    ui->stepEdit->setText(QString::number(configuration.altitudeStep));
}

void AltitudeForm::updateConfiguration(
        Configuration &configuration,
        UpdateOptions options) const
{
    if (!(options & Values)) return;

    configuration.altitudeUnits = (Configuration::AltitudeUnits) ui->unitsComboBox->currentIndex();
    configuration.altitudeStep = ui->stepEdit->text().toInt();
}
