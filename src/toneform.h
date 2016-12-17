#ifndef TONEFORM_H
#define TONEFORM_H

#include "configurationpage.h"

namespace Ui {
class ToneForm;
}

class ToneForm : public ConfigurationPage
{
    Q_OBJECT

public:
    explicit ToneForm(QWidget *parent = 0);
    ~ToneForm();

    QString title() const { return "Tone"; }

private:
    Ui::ToneForm *ui;
};

#endif // TONEFORM_H
