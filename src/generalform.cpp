#include "generalform.h"
#include "ui_generalform.h"

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
