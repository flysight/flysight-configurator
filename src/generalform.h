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

    void updateConfiguration(Configuration &configuration,
                             UpdateOptions options) const;
    void setConfiguration(const Configuration &configuration,
                          UpdateOptions options);

private:
    Ui::GeneralForm *ui;
};

#endif // GENERALFORM_H
