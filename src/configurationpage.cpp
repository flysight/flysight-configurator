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

#include "configurationpage.h"

ConfigurationPage::ConfigurationPage(QWidget *parent) :
    QWidget(parent)
{

}

void ConfigurationPage::updateConfiguration(
        Configuration &configuration,
        UpdateOptions options) const
{
    Q_UNUSED(configuration);
    Q_UNUSED(options);
}

void ConfigurationPage::setConfiguration(
        const Configuration &configuration)
{
    Q_UNUSED(configuration);
}
