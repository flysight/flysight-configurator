#ifndef MISCELLANEOUSFORM_H
#define MISCELLANEOUSFORM_H

#include "configurationpage.h"

namespace Ui {
class MiscellaneousForm;
}

class MiscellaneousForm : public ConfigurationPage
{
    Q_OBJECT

public:
    explicit MiscellaneousForm(QWidget *parent = 0);
    ~MiscellaneousForm();

    QString title() const { return "Miscellaneous"; }
    void updateConfiguration(Configuration &configuration);

private:
    Ui::MiscellaneousForm *ui;

public slots:
    void setConfiguration(const Configuration &configuration);
};

#endif // MISCELLANEOUSFORM_H