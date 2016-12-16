#ifndef GENERALFORM_H
#define GENERALFORM_H

#include <QWidget>

namespace Ui {
class GeneralForm;
}

class GeneralForm : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralForm(QWidget *parent = 0);
    ~GeneralForm();

private:
    Ui::GeneralForm *ui;
};

#endif // GENERALFORM_H
