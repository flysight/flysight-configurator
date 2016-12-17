#ifndef RATEFORM_H
#define RATEFORM_H

#include "configurationpage.h"

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

private:
    Ui::RateForm *ui;
};

#endif // RATEFORM_H
