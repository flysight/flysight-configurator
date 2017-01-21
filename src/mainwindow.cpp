#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QListWidget>
#include <QMessageBox>
#include <QStackedWidget>
#include <QTextStream>

#include "alarmform.h"
#include "configurationpage.h"
#include "generalform.h"
#include "initializationform.h"
#include "rateform.h"
#include "silenceform.h"
#include "speechform.h"
#include "thresholdsform.h"
#include "toneform.h"

#define MAX_ALARMS  10
#define MAX_WINDOWS 2

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create configuration pages
    pages.append(new GeneralForm());
    pages.append(new ToneForm());
    pages.append(new RateForm());
    pages.append(new SpeechForm());
    pages.append(new ThresholdsForm());
    pages.append(new InitializationForm());
    pages.append(new AlarmForm());
    pages.append(new SilenceForm());

    // Add pages to configuration window
    foreach(ConfigurationPage *page, pages)
    {
        ui->listWidget->addItem(page->title());
        ui->stackedWidget->addWidget(page);
        connect(this, SIGNAL(configurationChanged(Configuration)),
                page, SLOT(setConfiguration(Configuration)));
    }

    ui->listWidget->setCurrentRow(0);
    ui->stackedWidget->setCurrentIndex(0);

    // Connect list widget to stacked widget
    connect(ui->listWidget, SIGNAL(currentRowChanged(int)),
            ui->stackedWidget, SLOT(setCurrentIndex(int)));

    // Initial update
    emit configurationChanged(configuration);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open"),
                QString(),
                tr("Configuration files (*.txt)"));

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        configuration = Configuration();

        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();

            // Remove comments
            line = line.left(line.indexOf(';'));

            // Split into key/value
            QStringList cols = line.split(":");
            if (cols.length() < 2) continue;

            QString name = cols[0].trimmed();
            QString result = cols[1].trimmed();
            int val = result.toInt();

#define HANDLE_VALUE(s,w,t)\
    if (!name.compare(s)) { (w) = (t) (val); }

            HANDLE_VALUE("Model", configuration.model, Configuration::Model);
            HANDLE_VALUE("Rate", configuration.rate, int);

            HANDLE_VALUE("Mode", configuration.toneMode, Configuration::Mode);
            HANDLE_VALUE("Min", configuration.minTone, int);
            HANDLE_VALUE("Max", configuration.maxTone, int);
            HANDLE_VALUE("Limits", configuration.limits, Configuration::Limits);
            HANDLE_VALUE("Volume", configuration.toneVolume, int);

            HANDLE_VALUE("Mode_2", configuration.rateMode, Configuration::Mode);
            HANDLE_VALUE("Min_2", configuration.minRateValue, int);
            HANDLE_VALUE("Max_2", configuration.maxRateValue, int);
            HANDLE_VALUE("Min_Rate", configuration.minRate, int);
            HANDLE_VALUE("Max_Rate", configuration.maxRate, int);
            HANDLE_VALUE("Flatline", configuration.flatline, bool);

            HANDLE_VALUE("Sp_Mode", configuration.speechMode, Configuration::Mode);
            HANDLE_VALUE("Sp_Units", configuration.speechUnits, Configuration::Units);
            HANDLE_VALUE("Sp_Rate", configuration.speechRate, int);
            HANDLE_VALUE("Sp_Dec", configuration.speechDecimals, int);
            HANDLE_VALUE("Sp_Volume", configuration.speechVolume, int);

            HANDLE_VALUE("V_Thresh", configuration.vThreshold, int);
            HANDLE_VALUE("H_Thresh", configuration.hThreshold, int);

            HANDLE_VALUE("Use_SAS", configuration.adjustSpeed, bool);
            HANDLE_VALUE("TZ_Offset", configuration.timeZoneOffset, int);

            HANDLE_VALUE("Init_Mode", configuration.initMode, Configuration::InitMode);

            HANDLE_VALUE("Window", configuration.alarmWindowAbove, int);
            HANDLE_VALUE("Window", configuration.alarmWindowBelow, int);
            HANDLE_VALUE("Win_Above", configuration.alarmWindowAbove, int);
            HANDLE_VALUE("Win_Below", configuration.alarmWindowBelow, int);
            HANDLE_VALUE("DZ_Elev", configuration.groundElevation, int);

#undef HANDLE_VALUE

            if (!name.compare("Init_File"))
            {
                configuration.initFile = result;
            }

            if (!name.compare("Alarm_Elev") && configuration.alarms.length() < MAX_ALARMS)
            {
                Configuration::Alarm alarm;
                alarm.elevation = val;
                alarm.mode = Configuration::NoAlarm;
                alarm.file = QString();
                configuration.alarms.push_back(alarm);
            }
            if (!name.compare("Alarm_Type") && configuration.alarms.length() < MAX_ALARMS)
            {
                configuration.alarms.back().mode = (Configuration::AlarmMode) val;
            }
            if (!name.compare("Alarm_File") && configuration.alarms.length() < MAX_ALARMS)
            {
                configuration.alarms.back().file = result;
            }

            if (!name.compare("Window_Top") && configuration.windows.length() < MAX_WINDOWS)
            {
                Configuration::Window window;
                window.top = val;
                window.bottom = val;
                configuration.windows.push_back(window);
            }
            if (!name.compare("Window_Bottom") && configuration.windows.length() < MAX_WINDOWS)
            {
                configuration.windows.back().bottom = val;
            }
        }

        // Update configuration
        emit configurationChanged(configuration);
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("Couldn't open file"));
    }
}
