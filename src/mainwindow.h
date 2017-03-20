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

protected:
    void closeEvent(QCloseEvent *event);

private:
    typedef QVector< ConfigurationPage* > Pages;

    Ui::MainWindow *ui;

    Pages pages;
    Configuration configuration;
    Configuration savedConfiguration;
    Units currentUnits;

    bool updating;

    QString curFile;

    bool save();
    bool saveAs();

    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);

    void saveAlarm(QTextStream &out, const Configuration::Alarm &alarm, bool firstAlarm);
    void saveWindow(QTextStream &out, const Configuration::Window window);

    void setCurrentFile(const QString &fileName);
    bool maybeSave();

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();

    void setUnits(int newUnits);
    void updatePages();
    void updateConfigurationOptions();
};

#endif // MAINWINDOW_H
