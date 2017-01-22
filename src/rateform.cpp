#include "rateform.h"
#include "ui_rateform.h"

#include "configuration.h"

RateForm::RateForm(QWidget *parent) :
    ConfigurationPage(parent),
    ui(new Ui::RateForm)
{
    ui->setupUi(this);

    ui->modeComboBox->addItem("Horizontal speed");
    ui->modeComboBox->addItem("Vertical speed");
    ui->modeComboBox->addItem("Glide ratio");
    ui->modeComboBox->addItem("Inverse glide ratio");
    ui->modeComboBox->addItem("Total speed");
    ui->modeComboBox->addItem("Magnitude of tone value");
    ui->modeComboBox->addItem("Change in tone value");
}

RateForm::~RateForm()
{
    delete ui;
}

void RateForm::setConfiguration(const Configuration &configuration)
{
    switch (configuration.rateMode)
    {
    case Configuration::ValueChange:
    case Configuration::ValueMagnitude:
        ui->modeComboBox->setCurrentIndex(configuration.rateMode - 3);
        break;
    default:
        ui->modeComboBox->setCurrentIndex(configuration.rateMode);
    }

    ui->minimumValueEdit->setText(
                QString::number(configuration.minRateValue));
    ui->maximumValueEdit->setText(
                QString::number(configuration.maxRateValue));
    ui->minimumEdit->setText(
                QString::number(configuration.minRate));
    ui->maximumEdit->setText(
                QString::number(configuration.maxRate));
    ui->flatlineCheckBox->setChecked(configuration.flatline);
}

void RateForm::updateConfiguration(
        Configuration &configuration)
{
    int i = ui->modeComboBox->currentIndex();
    if (i <= 4) configuration.rateMode = (Configuration::Mode) i;
    else        configuration.rateMode = (Configuration::Mode) (i + 3);

    configuration.minRateValue = ui->minimumValueEdit->text().toInt();
    configuration.maxRateValue = ui->maximumValueEdit->text().toInt();
    configuration.minRate = ui->minimumEdit->text().toInt();
    configuration.maxRate = ui->maximumEdit->text().toInt();
    configuration.flatline = ui->flatlineCheckBox->isChecked();
}
