#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "configuration.h"

class ConfigurationPage;
class QTextStream;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    typedef enum {
        Metric = 0,
        Imperial
    } Units;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Units units() const { return currentUnits; }

private:
    typedef QVector< ConfigurationPage* > Pages;

    Ui::MainWindow *ui;

    Pages pages;
    Configuration configuration;
    Units currentUnits;

    bool updating;

    void saveAlarm(QTextStream &out, const Configuration::Alarm &alarm, bool firstAlarm);
    void saveWindow(QTextStream &out, const Configuration::Window window);

signals:
    void configurationChanged(const Configuration &configuration);

private slots:
    void on_openButton_clicked();
    void on_saveAsButton_clicked();

    void setUnits(int newUnits);
    void updatePages();
    void updateConfiguration();
};

#endif // MAINWINDOW_H
