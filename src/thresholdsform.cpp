#include "thresholdsform.h"
#include "ui_thresholdsform.h"

#include "configuration.h"

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

void ThresholdsForm::setConfiguration(const Configuration &configuration)
{
    ui->verticalEdit->setText(
                QString::number(configuration.vThreshold));
    ui->horizontalEdit->setText(
                QString::number(configuration.hThreshold));
}

void ThresholdsForm::updateConfiguration(
        Configuration &configuration)
{
    configuration.vThreshold = ui->verticalEdit->text().toInt();
    configuration.hThreshold = ui->horizontalEdit->text().toInt();
}
