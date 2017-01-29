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

    for (int i = 0; i <= 8; ++i)
    {
        ui->volumeComboBox->addItem(QString("%1%").arg(i / 8. * 100));
    }

    connect(ui->modeComboBox, SIGNAL(currentIndexChanged(int)),
            this, SIGNAL(selectionChanged()));
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
    ui->volumeComboBox->setCurrentIndex(configuration.toneVolume);

    Configuration::Mode mode
            = (Configuration::Mode) ui->modeComboBox->currentIndex();

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
    default:
        ui->minimumLabel->setText(tr("Minimum:"));
        ui->maximumLabel->setText(tr("Maximum:"));
        break;
    }
}

void ToneForm::updateConfiguration(
        Configuration &configuration)
{
    configuration.toneMode = (Configuration::Mode) ui->modeComboBox->currentIndex();
    configuration.minTone = ui->minimumEdit->text().toInt();
    configuration.maxTone = ui->maximumEdit->text().toInt();
    configuration.limits = (Configuration::Limits) ui->limitComboBox->currentIndex();
    configuration.toneVolume = ui->volumeComboBox->currentIndex();
}
