#ifndef SILENCEFORM_H
#define SILENCEFORM_H

#include "configurationpage.h"

namespace Ui {
class SilenceForm;
}

class SilenceForm : public ConfigurationPage
{
    Q_OBJECT

public:
    explicit SilenceForm(QWidget *parent = 0);
    ~SilenceForm();

    QString title() const { return "Silence"; }

private:
    Ui::SilenceForm *ui;

private slots:
    void add();
    void remove();
    void updateControls();
};

#endif // SILENCEFORM_H