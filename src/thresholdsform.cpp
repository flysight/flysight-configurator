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
    ui->verticalLabel->setText(
                tr("Vertical speed (%1):").arg(configuration.speedUnits()));
    ui->horizontalLabel->setText(
                tr("Horizontal speed (%1):").arg(configuration.speedUnits()));

    ui->verticalEdit->setText(
                QString::number(configuration.vThresholdToUnits()));
    ui->horizontalEdit->setText(
                QString::number(configuration.hThresholdToUnits()));
}

void ThresholdsForm::updateConfiguration(
        Configuration &configuration)
{
    configuration.vThresholdFromUnits(ui->verticalEdit->text().toDouble());
    configuration.hThresholdFromUnits(ui->horizontalEdit->text().toDouble());
}
