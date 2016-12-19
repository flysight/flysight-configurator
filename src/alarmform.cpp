#include "alarmform.h"
#include "ui_alarmform.h"

AlarmForm::AlarmForm(QWidget *parent) :
    ConfigurationPage(parent),
    ui(new Ui::AlarmForm)
{
    ui->setupUi(this);

    // Add headers
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(
                QStringList() << tr("Elevation") << tr("Type") << tr("Filename"));

    // Connect add/remove buttons
    connect(ui->addButton, SIGNAL(clicked(bool)),
            this, SLOT(add()));
    connect(ui->removeButton, SIGNAL(clicked(bool)),
            this, SLOT(remove()));

    // Update controls when selection changes
    connect(ui->tableWidget, SIGNAL(itemSelectionChanged()),
            this, SLOT(updateControls()));

    // Initial update
    updateControls();
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
    QModelIndexList list;
    while ((list = ui->tableWidget->selectionModel()->selectedIndexes()).size())
    {
        ui->tableWidget->model()->removeRow(list.first().row());
    }
}

void AlarmForm::updateControls()
{
    QItemSelectionModel *select = ui->tableWidget->selectionModel();
    ui->removeButton->setEnabled(select->hasSelection());
}
