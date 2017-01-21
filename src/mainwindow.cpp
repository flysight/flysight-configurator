#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QListWidget>
#include <QStackedWidget>

#include "alarmform.h"
#include "configurationpage.h"
#include "generalform.h"
#include "initializationform.h"
#include "rateform.h"
#include "silenceform.h"
#include "speechform.h"
#include "thresholdsform.h"
#include "toneform.h"

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
