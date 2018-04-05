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

#include "initializationform.h"
#include "ui_initializationform.h"

#include <QFileDialog>
#include <QFileInfo>

#include "configuration.h"

InitializationForm::InitializationForm(QWidget *parent) :
    ConfigurationPage(parent),
    ui(new Ui::InitializationForm)
{
    ui->setupUi(this);

    ui->modeComboBox->addItem("Do nothing");
    ui->modeComboBox->addItem("Test speech mode");
    ui->modeComboBox->addItem("Play file");
}

InitializationForm::~InitializationForm()
{
    delete ui;
}

void InitializationForm::setConfiguration(
        const Configuration &configuration)
{
    ui->modeComboBox->setCurrentIndex(configuration.initMode);
    ui->filenameEdit->setText(configuration.initFile);
}

void InitializationForm::updateConfiguration(
        Configuration &configuration,
        UpdateOptions options) const
{
    if (!(options & Values)) return;

    configuration.initMode = (Configuration::InitMode) ui->modeComboBox->currentIndex();
    configuration.initFile = ui->filenameEdit->text();
}
