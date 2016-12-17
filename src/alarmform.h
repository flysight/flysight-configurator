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

private:
    Ui::AlarmForm *ui;

private slots:
    void add();
    void remove();
};

#endif // ALARMFORM_H
