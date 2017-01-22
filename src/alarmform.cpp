#include "alarmform.h"
#include "ui_alarmform.h"

#include <QComboBox>

#include "configuration.h"

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

int AlarmForm::add()
{
    int i = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(i);

    ui->tableWidget->setItem(i, 0, new QTableWidgetItem());
    ui->tableWidget->setItem(i, 2, new QTableWidgetItem());

    QComboBox *combo = new QComboBox;

    combo->addItem("No alarm");
    combo->addItem("Beep");
    combo->addItem("Chirp up");
    combo->addItem("Chirp down");
    combo->addItem("Play file");

    ui->tableWidget->setCellWidget(i, 1, combo);

    return i;
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

void AlarmForm::setConfiguration(const Configuration &configuration)
{
    ui->windowAboveEdit->setText(
                QString::number(configuration.alarmWindowAbove));
    ui->windowBelowEdit->setText(
                QString::number(configuration.alarmWindowBelow));
    ui->groundElevationEdit->setText(
                QString::number(configuration.groundElevation));

    // Remove all alarms
    while (ui->tableWidget->rowCount() > 0)
    {
        ui->tableWidget->removeRow(0);
    }

    // Add alarms
    foreach (Configuration::Alarm alarm, configuration.alarms)
    {
        int i = add();

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(
                                     QString::number(alarm.elevation)));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(
                                     alarm.file));

        QComboBox *combo = (QComboBox*) ui->tableWidget->cellWidget(i, 1);
        combo->setCurrentIndex(alarm.mode);
    }
}

void AlarmForm::updateConfiguration(
        Configuration &configuration)
{
    configuration.alarmWindowAbove = ui->windowAboveEdit->text().toInt();
    configuration.alarmWindowBelow = ui->windowBelowEdit->text().toInt();
    configuration.groundElevation = ui->groundElevationEdit->text().toInt();

    // Clear alarms in configuration
    configuration.alarms.clear();

    // Add alarms from interface
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        Configuration::Alarm alarm;

        alarm.elevation = ui->tableWidget->item(i, 0)->text().toInt();
        alarm.file = ui->tableWidget->item(i, 2)->text();

        QComboBox *combo = (QComboBox*) ui->tableWidget->cellWidget(i, 1);
        alarm.mode = (Configuration::AlarmMode) combo->currentIndex();

        configuration.alarms.push_back(alarm);
    }
}
