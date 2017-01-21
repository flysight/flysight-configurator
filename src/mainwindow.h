#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "configuration.h"

class ConfigurationPage;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    typedef QVector< ConfigurationPage* > Pages;

    Ui::MainWindow *ui;

    Pages pages;
    Configuration configuration;

signals:
    void configurationChanged(const Configuration &configuration);

private slots:
    void on_openButton_clicked();
};

#endif // MAINWINDOW_H
