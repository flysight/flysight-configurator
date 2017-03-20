#include "generalform.h"
#include "ui_generalform.h"

#include "configuration.h"

GeneralForm::GeneralForm(QWidget *parent) :
    ConfigurationPage(parent),
    ui(new Ui::GeneralForm)
{
    ui->setupUi(this);

    ui->modelComboBox->addItem("Portable");
    ui->modelComboBox->addItem("Stationary");
    ui->modelComboBox->addItem("Pedestrian");
    ui->modelComboBox->addItem("Automotive");
    ui->modelComboBox->addItem("Sea");
    ui->modelComboBox->addItem("Airborne with < 1 G acceleration");
    ui->modelComboBox->addItem("Airborne with < 2 G acceleration");
    ui->modelComboBox->addItem("Airborne with < 4 G acceleration");
}

GeneralForm::~GeneralForm()
{
    delete ui;
}

void GeneralForm::setConfiguration(
        const Configuration &configuration)
{
    switch (configuration.model)
    {
    case Configuration::Portable:
        ui->modelComboBox->setCurrentIndex(configuration.model);
        break;
    default:
        ui->modelComboBox->setCurrentIndex(configuration.model - 1);
    }
    ui->rateSpinBox->setValue(configuration.rate);
}

void GeneralForm::updateConfiguration(
        Configuration &configuration,
        UpdateOptions options) const
{
    if (!(options & Values)) return;

    int i = ui->modelComboBox->currentIndex();
    if (i == 0) configuration.model = (Configuration::Model) i;
    else        configuration.model = (Configuration::Model) (i + 1);

    configuration.rate = ui->rateSpinBox->value();
}
