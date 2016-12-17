#include "thresholdsform.h"
#include "ui_thresholdsform.h"

ThresholdsForm::ThresholdsForm(QWidget *parent) :
    ConfigurationPage(parent),
    ui(new Ui::ThresholdsForm)
{
    ui->setupUi(this);
}

ThresholdsForm::~ThresholdsForm()
{
    delete ui;
}
