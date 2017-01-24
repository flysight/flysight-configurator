#include "configuration.h"

#define CMS_PER_KMH 27.77777777777778
#define CMS_PER_MPH 44.7

Configuration::Configuration(
        DisplayUnits units)
{
    displayUnits = units;

    model = Airborne1G;
    rate = 200;

    toneMode = GlideRatio;
    minTone = 0;
    maxTone = 300;
    limits = NoTone;
    toneVolume = 6;

    rateMode = ValueChange;
    minRateValue = 300;
    maxRateValue = 1500;
    minRate = 100;
    maxRate = 500;
    flatline = false;

    speechMode = GlideRatio;
    speechUnits = Kilometers;
    speechRate = 0;
    speechDecimals = 1;
    speechVolume = 8;

    vThreshold = 1000;
    hThreshold = 0;

    adjustSpeed = true;
    timeZoneOffset = 0;

    initMode = NoInit;
    initFile = QString("0");

    alarmWindowAbove = 0;
    alarmWindowBelow = 0;
    groundElevation = 0;

    alarms.clear();
    windows.clear();
}

QString Configuration::speedUnits() const
{
    switch (displayUnits)
    {
    case Metric: return "km/h";
    case Imperial: return "mph";
    }
    return "";
}

void Configuration::vThresholdFromUnits(
        double valueInUnits)
{
    vThreshold = valueFromSpeedUnits(valueInUnits);
}

double Configuration::vThresholdToUnits() const
{
    return valueToSpeedUnits(vThreshold);
}

void Configuration::hThresholdFromUnits(
        double valueInUnits)
{
    hThreshold = valueFromSpeedUnits(valueInUnits);
}

double Configuration::hThresholdToUnits() const
{
    return valueToSpeedUnits(hThreshold);
}

int Configuration::valueFromSpeedUnits(
        double valueInUnits) const
{
    switch (displayUnits)
    {
    case Metric: return valueInUnits * CMS_PER_KMH;
    case Imperial: return valueInUnits * CMS_PER_MPH;
    }
    return 0;
}

double Configuration::valueToSpeedUnits(
        int value) const
{
    switch (displayUnits)
    {
    case Metric: return value / CMS_PER_KMH;
    case Imperial: return value / CMS_PER_MPH;
    }
    return 0;
}
