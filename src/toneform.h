#ifndef TONEFORM_H
#define TONEFORM_H

#include "configurationpage.h"

class Configuration;

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

public slots:
    void setConfiguration(const Configuration &configuration);
};

#endif // TONEFORM_H
