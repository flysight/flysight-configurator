#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    typedef enum {
        Portable   = 0,
        Stationary = 2,
        Pedestrian = 3,
        Automotive = 4,
        Sea        = 5,
        Airborne1G = 6,
        Airborne2G = 7,
        Airborne4G = 8
    } Model;

    typedef enum {
        HorizontalSpeed   = 0,
        VerticalSpeed     = 1,
        GlideRatio        = 2,
        InverseGlideRatio = 3,
        TotalSpeed        = 4,
        ValueMagnitude    = 8,
        ValueChange       = 9
    } Mode;

    typedef enum {
        Silence      = 0,
        Clamp        = 1,
        Chirp        = 2,
        ChirpReverse = 3
    } Limits;

    typedef enum {
        km    = 0,
        miles = 1,
        knots = 2
    } Units;

    typedef enum {
        NoInit   = 0,
        InitTest = 1,
        InitFile = 2
    } InitMode;

    typedef enum {
        NoAlarm   = 0,
        Beep      = 1,
        ChirpUp   = 2,
        ChirpDown = 3,
        PlayFile  = 4
    } AlarmMode;

    typedef struct {
        int elevation;
        AlarmMode mode;
        QString file;
    } Alarm;

    typedef struct {
        int top;
        int bottom;
    } Window;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    typedef QVector< Alarm > Alarms;
    typedef QVector< Window > Windows;

    Ui::MainWindow *ui;

    Model model;
    int   rate;

    Mode toneMode;
    int minTone;
    int maxTone;
    Limits limits;
    int toneVolume;

    Mode rateMode;
    int minRateValue;
    int maxRateValue;
    int minRate;
    int maxRate;
    bool flatline;

    Mode speechMode;
    Units speechUnits;
    int speechRate;
    int speechDecimals;
    int speechVolume;

    int vThreshold;
    int hThreshold;

    bool adjustSpeed;
    int timeZoneOffset;

    InitMode initMode;
    QString initFile;

    int alarmWindowAbove;
    int alarmWindowBelow;
    int groundElevation;

    Alarms alarms;
    Windows windows;
};

#endif // MAINWINDOW_H
