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
    ui->modelComboBox->setCurrentIndex(configuration.model);
    ui->rateSpinBox->setValue(configuration.rate);
}

void GeneralForm::updateConfiguration(
        Configuration &configuration,
        UpdateOptions options) const
{
    if (!(options & Values)) return;

    configuration.model = (Configuration::Model) ui->modelComboBox->currentIndex();
    configuration.rate = ui->rateSpinBox->value();
}
