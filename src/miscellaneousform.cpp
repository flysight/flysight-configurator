#include "miscellaneousform.h"
#include "ui_miscellaneousform.h"

#include "configuration.h"

MiscellaneousForm::MiscellaneousForm(QWidget *parent) :
    ConfigurationPage(parent),
    ui(new Ui::MiscellaneousForm)
{
    ui->setupUi(this);
}

MiscellaneousForm::~MiscellaneousForm()
{
    delete ui;
}

void MiscellaneousForm::setConfiguration(
        const Configuration &configuration)
{
    ui->timezoneEdit->setText(
                QString::number(configuration.timeZoneOffset));
    ui->adjustedCheckBox->setChecked(configuration.adjustSpeed);
}

void MiscellaneousForm::updateConfiguration(
        Configuration &configuration,
        UpdateOptions options) const
{
    if (!(options & Values)) return;

    configuration.timeZoneOffset = ui->timezoneEdit->text().toInt();
    configuration.adjustSpeed = ui->adjustedCheckBox->isChecked();
}
