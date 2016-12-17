#include "speechform.h"
#include "ui_speechform.h"

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
