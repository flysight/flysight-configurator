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

    connect(ui->modeComboBox, SIGNAL(currentIndexChanged(int)),
            this, SIGNAL(selectionChanged()));
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
                QString::number(configuration.minRate / 100.));
    ui->maximumEdit->setText(
                QString::number(configuration.maxRate / 100.));
    ui->flatlineCheckBox->setChecked(configuration.flatline);

    Configuration::Mode mode;
    int i = ui->modeComboBox->currentIndex();
    if (i <= 4) mode = (Configuration::Mode) i;
    else        mode = (Configuration::Mode) (i + 3);

    switch((Configuration::Mode) mode)
    {
    case Configuration::HorizontalSpeed:
    case Configuration::VerticalSpeed:
    case Configuration::TotalSpeed:
        ui->minimumLabel->setText(tr("Minimum speed:"));
        ui->maximumLabel->setText(tr("Maximum speed:"));
        break;
    case Configuration::GlideRatio:
    case Configuration::InverseGlideRatio:
        ui->minimumLabel->setText(tr("Minimum glide ratio:"));
        ui->maximumLabel->setText(tr("Maximum glide ratio:"));
        break;
    case Configuration::ValueMagnitude:
        ui->minimumLabel->setText(tr("Minimum magnitude:"));
        ui->maximumLabel->setText(tr("Maximum magnitude:"));
        break;
    case Configuration::ValueChange:
        ui->minimumLabel->setText(tr("Minimum change:"));
        ui->maximumLabel->setText(tr("Maximum change:"));
        break;
    default:
        ui->minimumLabel->setText(tr("Minimum:"));
        ui->maximumLabel->setText(tr("Maximum:"));
        break;
    }
}

void RateForm::updateConfiguration(
        Configuration &configuration)
{
    int i = ui->modeComboBox->currentIndex();
    if (i <= 4) configuration.rateMode = (Configuration::Mode) i;
    else        configuration.rateMode = (Configuration::Mode) (i + 3);

    configuration.minRateValue = ui->minimumValueEdit->text().toInt();
    configuration.maxRateValue = ui->maximumValueEdit->text().toInt();
    configuration.minRate = ui->minimumEdit->text().toDouble() * 100;
    configuration.maxRate = ui->maximumEdit->text().toDouble() * 100;
    configuration.flatline = ui->flatlineCheckBox->isChecked();
}
