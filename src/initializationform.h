#ifndef INITIALIZATIONFORM_H
#define INITIALIZATIONFORM_H

#include "configurationpage.h"

namespace Ui {
class InitializationForm;
}

class InitializationForm : public ConfigurationPage
{
    Q_OBJECT

public:
    explicit InitializationForm(QWidget *parent = 0);
    ~InitializationForm();

    QString title() const { return "Initialization"; }

    void updateConfiguration(Configuration &configuration,
                             UpdateOptions options) const;
    void setConfiguration(const Configuration &configuration,
                          UpdateOptions options);

private:
    Ui::InitializationForm *ui;
};

#endif // INITIALIZATIONFORM_H
