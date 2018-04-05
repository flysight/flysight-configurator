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

#include "generalform.h"
#include "ui_generalform.h"

#include "configuration.h"

GeneralForm::GeneralForm(QWidget *parent) :
    ConfigurationPage(parent),
    ui(new Ui::GeneralForm)
{
    ui->setupUi(this);

    ui->modelComboBox->addItem("Portable");
    ui->modelComboBox->addItem("Stationary");
    ui->modelComboBox->addItem("Pedestrian");
    ui->modelComboBox->addItem("Automotive");
    ui->modelComboBox->addItem("Sea");
    ui->modelComboBox->addItem("Airborne with < 1 G acceleration");
    ui->modelComboBox->addItem("Airborne with < 2 G acceleration");
    ui->modelComboBox->addItem("Airborne with < 4 G acceleration");
}

GeneralForm::~GeneralForm()
{
    delete ui;
}

void GeneralForm::setConfiguration(
        const Configuration &configuration)
{
    switch (configuration.model)
    {
    case Configuration::Portable:
        ui->modelComboBox->setCurrentIndex(configuration.model);
        break;
    default:
        ui->modelComboBox->setCurrentIndex(configuration.model - 1);
    }
    ui->rateSpinBox->setValue(configuration.rate);
}

void GeneralForm::updateConfiguration(
        Configuration &configuration,
        UpdateOptions options) const
{
    if (!(options & Values)) return;

    int i = ui->modelComboBox->currentIndex();
    if (i == 0) configuration.model = (Configuration::Model) i;
    else        configuration.model = (Configuration::Model) (i + 1);

    configuration.rate = ui->rateSpinBox->value();
}
