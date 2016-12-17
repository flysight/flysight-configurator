#ifndef THRESHOLDSFORM_H
#define THRESHOLDSFORM_H

#include "configurationpage.h"

namespace Ui {
class ThresholdsForm;
}

class ThresholdsForm : public ConfigurationPage
{
    Q_OBJECT

public:
    explicit ThresholdsForm(QWidget *parent = 0);
    ~ThresholdsForm();

    QString title() const { return "Thresholds"; }

private:
    Ui::ThresholdsForm *ui;
};

#endif // THRESHOLDSFORM_H
