#ifndef RATEFORM_H
#define RATEFORM_H

#include "configurationpage.h"

class Configuration;

namespace Ui {
class RateForm;
}

class RateForm : public ConfigurationPage
{
    Q_OBJECT

public:
    explicit RateForm(QWidget *parent = 0);
    ~RateForm();

    QString title() const { return "Rate"; }
    void updateConfiguration(Configuration &configuration);

private:
    Ui::RateForm *ui;

public slots:
    void setConfiguration(const Configuration &configuration);
};

#endif // RATEFORM_H
