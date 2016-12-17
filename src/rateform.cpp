#include "rateform.h"
#include "ui_rateform.h"

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
