#include "speechform.h"
#include "ui_speechform.h"

#include "configuration.h"

SpeechForm::SpeechForm(QWidget *parent) :
    ConfigurationPage(parent),
    ui(new Ui::SpeechForm)
{
    ui->setupUi(this);

    ui->modeComboBox->addItem("Horizontal speed");
    ui->modeComboBox->addItem("Vertical speed");
    ui->modeComboBox->addItem("Glide ratio");
    ui->modeComboBox->addItem("Inverse glide ratio");
    ui->modeComboBox->addItem("Total speed");

    ui->unitsComboBox->addItem("km/h");
    ui->unitsComboBox->addItem("mph");
}

SpeechForm::~SpeechForm()
{
    delete ui;
}

void SpeechForm::setConfiguration(const Configuration &configuration)
{
    ui->modeComboBox->setCurrentIndex(configuration.speechMode);
    ui->unitsComboBox->setCurrentIndex(configuration.speechUnits);
    ui->rateEdit->setText(
                QString::number(configuration.speechRate));
    ui->decimalsSpinBox->setValue(configuration.speechDecimals);
    ui->volumeSpinBox->setValue(configuration.speechVolume);
}

void SpeechForm::updateConfiguration(
        Configuration &configuration)
{
    configuration.speechMode = (Configuration::Mode) ui->modeComboBox->currentIndex();
    configuration.speechUnits = (Configuration::Units) ui->unitsComboBox->currentIndex();
    configuration.speechRate = ui->rateEdit->text().toInt();
    configuration.speechDecimals = ui->decimalsSpinBox->value();
    configuration.speechVolume = ui->volumeSpinBox->value();
}
