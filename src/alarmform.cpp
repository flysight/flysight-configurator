#include "alarmform.h"
#include "ui_alarmform.h"

AlarmForm::AlarmForm(QWidget *parent) :
    ConfigurationPage(parent),
    ui(new Ui::AlarmForm)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(
                QStringList() << tr("Elevation") << tr("Type") << tr("Filename"));

    connect(ui->addButton, SIGNAL(clicked(bool)),
            this, SLOT(add()));
    connect(ui->removeButton, SIGNAL(clicked(bool)),
            this, SLOT(remove()));
}

AlarmForm::~AlarmForm()
{
    delete ui;
}

void AlarmForm::add()
{
    int i = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(i);
}

void AlarmForm::remove()
{
    int i = ui->tableWidget->currentRow();
    ui->tableWidget->removeRow(i);
}
