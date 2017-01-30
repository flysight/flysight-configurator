#include "silenceform.h"
#include "ui_silenceform.h"

#include <QComboBox>

#include "configuration.h"

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

int SilenceForm::add()
{
    int i = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(i);

    ui->tableWidget->setItem(i, 0, new QTableWidgetItem());
    ui->tableWidget->setItem(i, 1, new QTableWidgetItem());

    return i;
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

void SilenceForm::setConfiguration(
        const Configuration &configuration,
        UpdateOptions options)
{
    if (!(options & Values)) return;

    ui->tableWidget->setHorizontalHeaderLabels(
                QStringList()
                << tr("Top (%1)").arg(configuration.distanceUnits())
                << tr("Bottom (%1)").arg(configuration.distanceUnits()));

    // Remove all silence windows
    while (ui->tableWidget->rowCount() > 0)
    {
        ui->tableWidget->removeRow(0);
    }

    // Add silence windows
    foreach (Configuration::Window window, configuration.windows)
    {
        int i = add();

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(
                                     QString::number(configuration.valueToDistanceUnits(
                                                         window.top))));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(
                                     QString::number(configuration.valueToDistanceUnits(
                                                         window.bottom))));
    }
}

void SilenceForm::updateConfiguration(
        Configuration &configuration,
        UpdateOptions options) const
{
    if (!(options & Values)) return;

    // Clear windows in configuration
    configuration.windows.clear();

    // Add windows from interface
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        Configuration::Window window;

        if (ui->tableWidget->item(i, 0)->text()
                != QString::number(configuration.valueToDistanceUnits(
                                       window.top)))
        {
            window.top = configuration.valueFromDistanceUnits(
                        ui->tableWidget->item(i, 0)->text().toDouble());
        }
        if (ui->tableWidget->item(i, 1)->text()
                != QString::number(configuration.valueToDistanceUnits(
                                       window.bottom)))
        {
            window.bottom = configuration.valueFromDistanceUnits(
                        ui->tableWidget->item(i, 1)->text().toDouble());
        }

        configuration.windows.push_back(window);
    }
}
