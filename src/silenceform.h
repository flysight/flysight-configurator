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

#ifndef SILENCEFORM_H
#define SILENCEFORM_H

#include "configurationpage.h"

namespace Ui {
class SilenceForm;
}

class SilenceForm : public ConfigurationPage
{
    Q_OBJECT

public:
    explicit SilenceForm(QWidget *parent = 0);
    ~SilenceForm();

    QString title() const { return "Silence"; }

    void updateConfiguration(Configuration &configuration,
                             UpdateOptions options) const;
    void setConfiguration(const Configuration &configuration);

private:
    Ui::SilenceForm *ui;

private slots:
    int add();
    void remove();
    void updateControls();
};

#endif // SILENCEFORM_H
