#include "generalform.h"
#include "ui_generalform.h"

GeneralForm::GeneralForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeneralForm)
{
    ui->setupUi(this);
}

GeneralForm::~GeneralForm()
{
    delete ui;
}
