#ifndef ALARMFORM_H
#define ALARMFORM_H

#include "configurationpage.h"

class Configuration;

namespace Ui {
class AlarmForm;
}

class AlarmForm : public ConfigurationPage
{
    Q_OBJECT

public:
    explicit AlarmForm(QWidget *parent = 0);
    ~AlarmForm();

    QString title() const { return "Alarms"; }

private:
    Ui::AlarmForm *ui;

public slots:
    void setConfiguration(const Configuration &configuration);

private slots:
    int add();
    void remove();
    void updateControls();
};

#endif // ALARMFORM_H
