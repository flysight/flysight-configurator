#include "silenceform.h"
#include "ui_silenceform.h"

#include <QComboBox>

SilenceForm::SilenceForm(QWidget *parent) :
    ConfigurationPage(parent),
    ui(new Ui::SilenceForm)
{
    ui->setupUi(this);

    // Add headers
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(
                QStringList() << tr("Top") << tr("Bottom"));

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

SilenceForm::~SilenceForm()
{
    delete ui;
}

void SilenceForm::add()
{
    int i = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(i);
}

void SilenceForm::remove()
{
    QModelIndexList list;
    while ((list = ui->tableWidget->selectionModel()->selectedIndexes()).size())
    {
        ui->tableWidget->model()->removeRow(list.first().row());
    }
}

void SilenceForm::updateControls()
{
    QItemSelectionModel *select = ui->tableWidget->selectionModel();
    ui->removeButton->setEnabled(select->hasSelection());
}
