#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QListWidget>
#include <QMessageBox>
#include <QSettings>
#include <QStackedWidget>
#include <QTextStream>

#include "alarmform.h"
#include "configurationpage.h"
#include "generalform.h"
#include "initializationform.h"
#include "miscellaneousform.h"
#include "rateform.h"
#include "silenceform.h"
#include "speechform.h"
#include "thresholdsform.h"
#include "toneform.h"

#define MAX_ALARMS  10
#define MAX_WINDOWS 2

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    updating(false)
{
    ui->setupUi(this);

    // Create configuration pages
    pages.append(new GeneralForm());
    pages.append(new ToneForm());
    pages.append(new RateForm());
    pages.append(new SpeechForm());
    pages.append(new ThresholdsForm());
    pages.append(new MiscellaneousForm());
    pages.append(new InitializationForm());
    pages.append(new AlarmForm());
    pages.append(new SilenceForm());

    // Add pages to configuration window
    foreach(ConfigurationPage *page, pages)
    {
        ui->listWidget->addItem(page->title());
        ui->stackedWidget->addWidget(page);

        connect(page, SIGNAL(selectionChanged()),
                this, SLOT(updateConfigurationOptions()));
    }

    ui->listWidget->setCurrentRow(0);
    ui->stackedWidget->setCurrentIndex(0);

    // Connect list widget to stacked widget
    connect(ui->listWidget, SIGNAL(currentRowChanged(int)),
            ui->stackedWidget, SLOT(setCurrentIndex(int)));

    // Initialize units list
    ui->unitsComboBox->addItem("Metric");
    ui->unitsComboBox->addItem("Imperial");

    // Watch for unit changes
    connect(ui->unitsComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(setUnits(int)));

    // Initial update
    updatePages();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openButton_clicked()
{
    // Initialize settings object
    QSettings settings("FlySight", "Configurator");

    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open"),
                settings.value("folder").toString(),
                tr("Configuration files (*.txt)"));

    // Return now if user canceled
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // Remember last file read
        settings.setValue("folder", QFileInfo(fileName).absoluteFilePath());

        // Reset configuration but keep units
        configuration = Configuration(configuration.displayUnits);

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

            if (!name.compare("Win_Top") && configuration.windows.length() < MAX_WINDOWS)
            {
                Configuration::Window window;
                window.top = val;
                window.bottom = val;
                configuration.windows.push_back(window);
            }
            if (!name.compare("Win_Bottom") && configuration.windows.length() < MAX_WINDOWS)
            {
                configuration.windows.back().bottom = val;
            }
        }

        // Update configuration
        updatePages();
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("Couldn't open file"));
    }
}

void MainWindow::on_saveAsButton_clicked()
{
    // Initialize settings object
    QSettings settings("FlySight", "Configurator");

    QString fileName = QFileDialog::getSaveFileName(
                this,
                tr("Save As"),
                settings.value("folder").toString(),
                tr("Configuration files (*.txt)"));

    // Return now if user canceled
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // Remember last file read
        settings.setValue("folder", QFileInfo(fileName).absoluteFilePath());

        // Update configuration
        foreach(ConfigurationPage *page, pages)
        {
            page->updateConfiguration(configuration, ConfigurationPage::Values);
        }

        QTextStream out(&file);

        out << "; For information on configuring FlySight, please go to" << endl;
        out << ";     http://flysight.ca/wiki" << endl << endl;

        out << "; GPS settings" << endl << endl;

        out << "Model:      " << QString("%1").arg(configuration.model, 5) << " ; Dynamic model" << endl;
        out << "                  ;   0 = Portable" << endl;
        out << "                  ;   2 = Stationary" << endl;
        out << "                  ;   3 = Pedestrian" << endl;
        out << "                  ;   4 = Automotive" << endl;
        out << "                  ;   5 = Sea" << endl;
        out << "                  ;   6 = Airborne with < 1 G acceleration" << endl;
        out << "                  ;   7 = Airborne with < 2 G acceleration" << endl;
        out << "                  ;   8 = Airborne with < 4 G acceleration" << endl;
        out << "Rate:       " << QString("%1").arg(configuration.rate, 5) << " ; Measurement rate (ms)" << endl << endl;

        out << "; Tone settings" << endl << endl;

        out << "Mode:       " << QString("%1").arg(configuration.toneMode, 5) << " ; Measurement mode" << endl;
        out << "                  ;   0 = Horizontal speed" << endl;
        out << "                  ;   1 = Vertical speed" << endl;
        out << "                  ;   2 = Glide ratio" << endl;
        out << "                  ;   3 = Inverse glide ratio" << endl;
        out << "                  ;   4 = Total speed" << endl;
        out << "Min:        " << QString("%1").arg(configuration.minTone, 5) << " ; Lowest pitch value" << endl;
        out << "                  ;   cm/s        in Mode 0, 1, or 4" << endl;
        out << "                  ;   ratio * 100 in Mode 2 or 3" << endl;
        out << "Max:        " << QString("%1").arg(configuration.maxTone, 5) << " ; Highest pitch value" << endl;
        out << "                  ;   cm/s        in Mode 0, 1, or 4" << endl;
        out << "                  ;   ratio * 100 in Mode 2 or 3" << endl;
        out << "Limits:     " << QString("%1").arg(configuration.limits, 5) << " ; Behaviour when outside bounds" << endl;
        out << "                  ;   0 = No tone" << endl;
        out << "                  ;   1 = Min/max tone" << endl;
        out << "                  ;   2 = Chirp up/down" << endl;
        out << "                  ;   3 = Chirp down/up" << endl;
        out << "Volume:     " << QString("%1").arg(configuration.toneVolume, 5) << " ; 0 (min) to 8 (max)" << endl << endl;

        out << "; Rate settings" << endl << endl;

        out << "Mode_2:     " << QString("%1").arg(configuration.rateMode, 5) << " ; Determines tone rate" << endl;
        out << "                  ;   0 = Horizontal speed" << endl;
        out << "                  ;   1 = Vertical speed" << endl;
        out << "                  ;   2 = Glide ratio" << endl;
        out << "                  ;   3 = Inverse glide ratio" << endl;
        out << "                  ;   4 = Total speed" << endl;
        out << "                  ;   8 = Magnitude of Value 1" << endl;
        out << "                  ;   9 = Change in Value 1" << endl;
        out << "Min_Val_2:  " << QString("%1").arg(configuration.minRateValue, 5) << " ; Lowest rate value" << endl;
        out << "                  ;   cm/s          when Mode 2 = 0, 1, or 4" << endl;
        out << "                  ;   ratio * 100   when Mode 2 = 2 or 3" << endl;
        out << "                  ;   percent * 100 when Mode 2 = 9" << endl;
        out << "Max_Val_2:  " << QString("%1").arg(configuration.maxRateValue, 5) << " ; Highest rate value" << endl;
        out << "                  ;   cm/s          when Mode 2 = 0, 1, or 4" << endl;
        out << "                  ;   ratio * 100   when Mode 2 = 2 or 3" << endl;
        out << "                  ;   percent * 100 when Mode 2 = 9" << endl;
        out << "Min_Rate:   " << QString("%1").arg(configuration.minRate, 5) << " ; Minimum rate (Hz * 100)" << endl;
        out << "Max_Rate:   " << QString("%1").arg(configuration.maxRate, 5) << " ; Maximum rate (Hz * 100)" << endl;
        out << "Flatline:   " << QString("%1").arg(configuration.flatline, 5) << " ; Flatline at minimum rate" << endl;
        out << "                  ;   0 = No" << endl;
        out << "                  ;   1 = Yes" << endl << endl;

        out << "; Speech settings" << endl << endl;

        out << "Sp_Mode:    " << QString("%1").arg(configuration.speechMode, 5) << " ; Speech mode" << endl;
        out << "                  ;   0 = Horizontal speed" << endl;
        out << "                  ;   1 = Vertical speed" << endl;
        out << "                  ;   2 = Glide ratio" << endl;
        out << "                  ;   3 = Inverse glide ratio" << endl;
        out << "                  ;   4 = Total speed" << endl;
        out << "Sp_Units:   " << QString("%1").arg(configuration.speechUnits, 5) << " ; Speech units" << endl;
        out << "                  ;   0 = km/h" << endl;
        out << "                  ;   1 = mph" << endl;
        out << "Sp_Rate:    " << QString("%1").arg(configuration.speechRate, 5) << " ; Speech rate (s)" << endl;
        out << "                  ;   0 = No speech" << endl;
        out << "Sp_Dec:     " << QString("%1").arg(configuration.speechDecimals, 5) << " ; Decimal places for speech" << endl;
        out << "Sp_Volume:  " << QString("%1").arg(configuration.speechVolume, 5) << " ; 0 (min) to 8 (max)" << endl << endl;

        out << "; Thresholds" << endl << endl;

        out << "V_Thresh:   " << QString("%1").arg(configuration.vThreshold, 5) << " ; Minimum vertical speed for tone (cm/s)" << endl;
        out << "H_Thresh:   " << QString("%1").arg(configuration.hThreshold, 5) << " ; Minimum horizontal speed for tone (cm/s)" << endl << endl;

        out << "; Miscellaneous" << endl << endl;

        out << "Use_SAS:    " << QString("%1").arg(configuration.adjustSpeed, 5) << " ; Use skydiver's airspeed" << endl;
        out << "                  ;   0 = No" << endl;
        out << "                  ;   1 = Yes" << endl;
        out << "TZ_Offset:  " << QString("%1").arg(configuration.timeZoneOffset, 5) << " ; Timezone offset of output files in seconds" << endl;
        out << "                  ;   -14400 = UTC-4 (EDT)" << endl;
        out << "                  ;   -18000 = UTC-5 (EST, CDT)" << endl;
        out << "                  ;   -21600 = UTC-6 (CST, MDT)" << endl;
        out << "                  ;   -25200 = UTC-7 (MST, PDT)" << endl;
        out << "                  ;   -28800 = UTC-8 (PST)" << endl << endl;

        out << "; Initialization" << endl << endl;

        out << "Init_Mode:  " << QString("%1").arg(configuration.initMode, 5) << " ; When the FlySight is powered on" << endl;
        out << "                  ;   0 = Do nothing" << endl;
        out << "                  ;   1 = Test speech mode" << endl;
        out << "                  ;   2 = Play file" << endl;
        out << "Init_File:  " << configuration.initFile.rightJustified(5) << " ; File to be played" << endl << endl;

        out << "; Alarm settings" << endl << endl;

        out << "; WARNING: GPS measurements depend on very weak signals" << endl;
        out << ";          received from orbiting satellites. As such, they" << endl;
        out << ";          are prone to interference, and should NEVER be" << endl;
        out << ";          relied upon for life saving purposes." << endl << endl;

        out << ";          UNDER NO CIRCUMSTANCES SHOULD THESE ALARMS BE" << endl;
        out << ";          USED TO INDICATE DEPLOYMENT OR BREAKOFF ALTITUDE." << endl << endl;

        out << "; NOTE:    Alarm elevations are given in meters above ground" << endl;
        out << ";          elevation, which is specified in DZ_Elev." << endl << endl;

        out << "Win_Above:  " << QString("%1").arg(configuration.alarmWindowAbove, 5) << " ; Alarm window (m)" << endl;
        out << "Win_Below:  " << QString("%1").arg(configuration.alarmWindowBelow, 5) << " ; Alarm window (m)" << endl;
        out << "DZ_Elev:    " << QString("%1").arg(configuration.groundElevation, 5) << " ; Ground elevation (m above sea level)" << endl << endl;

        if (configuration.alarms.empty())
        {
            Configuration::Alarm alarm;
            alarm.elevation = 0;
            alarm.mode = Configuration::NoAlarm;
            alarm.file = "0";
            saveAlarm(out, alarm, true);
        }
        else
        {
            bool firstAlarm = true;
            foreach (Configuration::Alarm alarm, configuration.alarms)
            {
                saveAlarm(out, alarm, firstAlarm);
                firstAlarm = false;
            }
        }

        out << "; Silence windows" << endl << endl;

        out << "; NOTE:    Silence windows are given in meters above ground" << endl;
        out << ";          elevation, which is specified in DZ_Elev. Tones" << endl;
        out << ";          will be silenced during these windows and only" << endl;
        out << ";          alarms will be audible." << endl << endl;

        if (configuration.windows.empty())
        {
            Configuration::Window window;
            window.top = 0;
            window.bottom = 0;
            saveWindow(out, window);
        }
        else
        {
            foreach (Configuration::Window window, configuration.windows)
            {
                saveWindow(out, window);
            }
        }
    }
}

void MainWindow::saveAlarm(
        QTextStream &out,
        const Configuration::Alarm &alarm,
        bool firstAlarm)
{
    out << "Alarm_Elev: " << QString("%1").arg(alarm.elevation, 5) << " ; Alarm elevation (m above ground level)" << endl;
    out << "Alarm_Type: " << QString("%1").arg(alarm.mode, 5) << " ; Alarm type" << endl;
    if (firstAlarm)
    {
        out << "                  ;   0 = No alarm" << endl;
        out << "                  ;   1 = Beep" << endl;
        out << "                  ;   2 = Chirp up" << endl;
        out << "                  ;   3 = Chirp down" << endl;
        out << "                  ;   4 = Play file" << endl;
    }
    out << "Alarm_File: " << alarm.file.rightJustified(5) << " ; File to be played" << endl << endl;
}

void MainWindow::saveWindow(
        QTextStream &out,
        const Configuration::Window window)
{
    out << "Win_Top:    " << QString("%1").arg(window.top, 5) << " ; Silence window top (m)" << endl;
    out << "Win_Bottom: " << QString("%1").arg(window.bottom, 5) << " ; Silence window bottom (m)" << endl << endl;
}

void MainWindow::setUnits(
        int units)
{
    if (configuration.displayUnits == (Configuration::DisplayUnits) units)
        return;

    // Update configuration from pages
    foreach(ConfigurationPage *page, pages)
    {
        page->updateConfiguration(configuration, ConfigurationPage::Values);
    }

    // Update display units
    configuration.displayUnits = (Configuration::DisplayUnits) units;
    ui->unitsComboBox->setCurrentIndex(units);

    // Update pages from configuration
    updatePages();
}

void MainWindow::updateConfigurationOptions()
{
    if (updating) return;

    // Update configuration from pages
    foreach(ConfigurationPage *page, pages)
    {
        page->updateConfiguration(configuration, ConfigurationPage::Values);
    }
    foreach(ConfigurationPage *page, pages)
    {
        page->updateConfiguration(configuration, ConfigurationPage::Options);
    }

    // Now update the configuration pages
    updatePages();
}

void MainWindow::updatePages()
{
    updating = true;

    // Update pages from configuration
    foreach(ConfigurationPage *page, pages)
    {
        page->setConfiguration(configuration);
    }

    updating = false;
}
