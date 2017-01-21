#include "toneform.h"
#include "ui_toneform.h"

#include "configuration.h"

ToneForm::ToneForm(QWidget *parent) :
    ConfigurationPage(parent),
    ui(new Ui::ToneForm)
{
    ui->setupUi(this);

    ui->modeComboBox->addItem("Horizontal speed");
    ui->modeComboBox->addItem("Vertical speed");
    ui->modeComboBox->addItem("Glide ratio");
    ui->modeComboBox->addItem("Inverse glide ratio");
    ui->modeComboBox->addItem("Total speed");

    ui->limitComboBox->addItem("No tone");
    ui->limitComboBox->addItem("Min/max tone");
    ui->limitComboBox->addItem("Chirp up/down");
    ui->limitComboBox->addItem("Chrip down/up");
}

ToneForm::~ToneForm()
{
    delete ui;
}

void ToneForm::setConfiguration(const Configuration &configuration)
{
    ui->modeComboBox->setCurrentIndex(configuration.toneMode);
    ui->minimumEdit->setText(
                QString::number(configuration.minTone));
    ui->maximumEdit->setText(
                QString::number(configuration.maxTone));
    ui->limitComboBox->setCurrentIndex(configuration.limits);
    ui->volumeSpinBox->setValue(configuration.toneVolume);
}
