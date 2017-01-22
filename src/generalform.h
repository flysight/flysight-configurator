#ifndef GENERALFORM_H
#define GENERALFORM_H

#include "configurationpage.h"

namespace Ui {
class GeneralForm;
}

class GeneralForm : public ConfigurationPage
{
    Q_OBJECT

public:
    explicit GeneralForm(QWidget *parent = 0);
    ~GeneralForm();

    QString title() const { return "General"; }

private:
    Ui::GeneralForm *ui;

public slots:
    void setConfiguration(const Configuration &configuration);
};

#endif // GENERALFORM_H
