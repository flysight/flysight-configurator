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
    void updateConfiguration(Configuration &configuration);

private:
    Ui::InitializationForm *ui;

public slots:
    void setConfiguration(const Configuration &configuration);
};

#endif // INITIALIZATIONFORM_H
