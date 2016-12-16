#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "configuration.h"

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
    typedef QVector< QWidget* > Pages;

    Ui::MainWindow *ui;

    Pages pages;
    Configuration configuration;
};

#endif // MAINWINDOW_H
