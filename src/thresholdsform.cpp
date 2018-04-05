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

#include "thresholdsform.h"
#include "ui_thresholdsform.h"

#include "configuration.h"

ThresholdsForm::ThresholdsForm(QWidget *parent) :
    ConfigurationPage(parent),
    ui(new Ui::ThresholdsForm)
{
    ui->setupUi(this);
}

ThresholdsForm::~ThresholdsForm()
{
    delete ui;
}

void ThresholdsForm::setConfiguration(
        const Configuration &configuration)
{
    ui->verticalLabel->setText(
                tr("Vertical speed (%1):").arg(configuration.speedUnits()));
    ui->horizontalLabel->setText(
                tr("Horizontal speed (%1):").arg(configuration.speedUnits()));

    ui->verticalEdit->setText(
                QString::number(configuration.vThresholdToUnits()));
    ui->horizontalEdit->setText(
                QString::number(configuration.hThresholdToUnits()));
}

void ThresholdsForm::updateConfiguration(
        Configuration &configuration,
        UpdateOptions options) const
{
    if (!(options & Values)) return;

    if (ui->verticalEdit->text()
            != QString::number(configuration.vThresholdToUnits()))
    {
        configuration.vThresholdFromUnits(ui->verticalEdit->text().toDouble());
    }
    if (ui->horizontalEdit->text()
            != QString::number(configuration.hThresholdToUnits()))
    {
        configuration.hThresholdFromUnits(ui->horizontalEdit->text().toDouble());
    }
}
