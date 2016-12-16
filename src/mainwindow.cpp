#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QStackedWidget>

#include "generalform.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create configuration pages
    pages.append(new GeneralForm());

    // Add pages to configuration window
    QStackedWidget *stackedWidget = new QStackedWidget();
    foreach(QWidget *widget, pages)
    {
        stackedWidget->addWidget(widget);
    }
    stackedWidget->setCurrentIndex(0);

    // Lay out main window
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(stackedWidget);

    // Create new central widget
    QWidget *window = new QWidget();
    window->setLayout(layout);

    // Set the new central widget
    setCentralWidget(window);
}

MainWindow::~MainWindow()
{
    delete ui;
}
