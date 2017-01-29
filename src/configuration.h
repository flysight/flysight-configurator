#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>
#include <QVector>

class Configuration
{
public:
    typedef enum {
        Metric = 0,
        Imperial
    } DisplayUnits;

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
        NoTone       = 0,
        Clamp        = 1,
        Chirp        = 2,
        ChirpReverse = 3
    } Limits;

    typedef enum {
        Kilometers = 0,
        Miles      = 1,
        Knots      = 2
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

    typedef QVector< Alarm > Alarms;
    typedef QVector< Window > Windows;

    DisplayUnits displayUnits;

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

    Configuration(DisplayUnits units = Metric);

    QString speedUnits() const;
    QString distanceUnits() const;

    void vThresholdFromUnits(double valueInUnits);
    double vThresholdToUnits() const;

    void hThresholdFromUnits(double valueInUnits);
    double hThresholdToUnits() const;

    void alarmWindowAboveFromUnits(double valueInUnits);
    double alarmWindowAboveToUnits() const;

    void alarmWindowBelowFromUnits(double valueInUnits);
    double alarmWindowBelowToUnits() const;

    void groundElevationFromUnits(double valueInUnits);
    double groundElevationToUnits() const;

    int valueFromSpeedUnits(double valueInUnits) const;
    double valueToSpeedUnits(int value) const;

    int valueFromDistanceUnits(double valueInUnits) const;
    double valueToDistanceUnits(int value) const;

    double minToneToUnits() const;
    void minToneFromUnits(double valueInUnits);

    double maxToneToUnits() const;
    void maxToneFromUnits(double valueInUnits);

    double toneToUnits(int value) const;
    int toneFromUnits(double valueInUnits) const;
};

#endif // CONFIGURATION_H
