#ifndef ALARMFORM_H
#define ALARMFORM_H

#include "configurationpage.h"

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

    void updateConfiguration(Configuration &configuration,
                             UpdateOptions options) const;
    void setConfiguration(const Configuration &configuration,
                          UpdateOptions options);

private:
    Ui::AlarmForm *ui;

private slots:
    int add();
    void remove();
    void updateControls();
};

#endif // ALARMFORM_H
