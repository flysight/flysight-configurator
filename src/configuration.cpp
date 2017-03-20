#include "configuration.h"

#define CMS_PER_KMH 27.77777777777778
#define CMS_PER_MPH 44.70416666666667
#define M_PER_FT    0.3048

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

QString Configuration::distanceUnits() const
{
    switch (displayUnits)
    {
    case Metric: return "m";
    case Imperial: return "ft";
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

void Configuration::alarmWindowAboveFromUnits(
        double valueInUnits)
{
    alarmWindowAbove = valueFromDistanceUnits(valueInUnits);
}

double Configuration::alarmWindowAboveToUnits() const
{
    return valueToDistanceUnits(alarmWindowAbove);
}

double Configuration::alarmWindowBelowToUnits() const
{
    return valueToDistanceUnits(alarmWindowBelow);
}

void Configuration::alarmWindowBelowFromUnits(
        double valueInUnits)
{
    alarmWindowBelow = valueFromDistanceUnits(valueInUnits);
}

double Configuration::groundElevationToUnits() const
{
    return valueToDistanceUnits(groundElevation);
}

void Configuration::groundElevationFromUnits(
        double valueInUnits)
{
    groundElevation = valueFromDistanceUnits(valueInUnits);
}

int Configuration::valueFromSpeedUnits(
        double valueInUnits) const
{
    switch (displayUnits)
    {
    case Metric: return valueInUnits * CMS_PER_KMH;
    case Imperial: return (valueInUnits * CMS_PER_MPH + 0.5);
    }
    return 0;
}

double Configuration::valueToSpeedUnits(
        int value) const
{
    switch (displayUnits)
    {
    case Metric: return value / (double) CMS_PER_KMH;
    case Imperial: return value / (double) CMS_PER_MPH;
    }
    return 0;
}

int Configuration::valueFromDistanceUnits(
        double valueInUnits) const
{
    switch (displayUnits)
    {
    case Metric: return valueInUnits;
    case Imperial: return (valueInUnits * M_PER_FT + 0.5);
    }
    return 0;
}

double Configuration::valueToDistanceUnits(
        int value) const
{
    switch (displayUnits)
    {
    case Metric: return value;
    case Imperial: return value / (double) M_PER_FT;
    }
    return 0;
}

double Configuration::minToneToUnits() const
{
    return toneToUnits(minTone);
}

void Configuration::minToneFromUnits(
        double valueInUnits)
{
    minTone = toneFromUnits(valueInUnits);
}

double Configuration::maxToneToUnits() const
{
    return toneToUnits(maxTone);
}

void Configuration::maxToneFromUnits(
        double valueInUnits)
{
    maxTone = toneFromUnits(valueInUnits);
}

double Configuration::toneToUnits(
        int value) const
{
    switch(toneMode)
    {
    case Configuration::HorizontalSpeed:
    case Configuration::VerticalSpeed:
    case Configuration::TotalSpeed:
        return valueToSpeedUnits(value);
    case Configuration::GlideRatio:
    case Configuration::InverseGlideRatio:
        return value / 100.;
    default:
        return value;
    }
}

int Configuration::toneFromUnits(
        double valueInUnits) const
{
    switch(toneMode)
    {
    case Configuration::HorizontalSpeed:
    case Configuration::VerticalSpeed:
    case Configuration::TotalSpeed:
        return valueFromSpeedUnits(valueInUnits);
    case Configuration::GlideRatio:
    case Configuration::InverseGlideRatio:
        return valueInUnits * 100;
    default:
        return valueInUnits;
    }
}

double Configuration::minRateToUnits() const
{
    return rateToUnits(minRateValue);
}

void Configuration::minRateFromUnits(
        double valueInUnits)
{
    minRateValue = rateFromUnits(valueInUnits);
}

double Configuration::maxRateToUnits() const
{
    return rateToUnits(maxRateValue);
}

void Configuration::maxRateFromUnits(
        double valueInUnits)
{
    maxRateValue = rateFromUnits(valueInUnits);
}

double Configuration::rateToUnits(
        int value) const
{
    switch(rateMode)
    {
    case Configuration::HorizontalSpeed:
    case Configuration::VerticalSpeed:
    case Configuration::TotalSpeed:
        return valueToSpeedUnits(value);
    case Configuration::GlideRatio:
    case Configuration::InverseGlideRatio:
        return value / 100.;
    case Configuration::ValueMagnitude:
        switch (toneMode)
        {
        case Configuration::HorizontalSpeed:
        case Configuration::VerticalSpeed:
        case Configuration::TotalSpeed:
            return valueToSpeedUnits(value);
        case Configuration::GlideRatio:
        case Configuration::InverseGlideRatio:
            return value / 100.;
        default:
            return value;
        }
    case Configuration::ValueChange:
        return value / 100.;
    default:
        return value;
    }
}

int Configuration::rateFromUnits(
        double valueInUnits) const
{
    switch(rateMode)
    {
    case Configuration::HorizontalSpeed:
    case Configuration::VerticalSpeed:
    case Configuration::TotalSpeed:
        return valueFromSpeedUnits(valueInUnits);
    case Configuration::GlideRatio:
    case Configuration::InverseGlideRatio:
        return valueInUnits * 100;
    case Configuration::ValueMagnitude:
        switch (toneMode)
        {
        case Configuration::HorizontalSpeed:
        case Configuration::VerticalSpeed:
        case Configuration::TotalSpeed:
            return valueFromSpeedUnits(valueInUnits);
        case Configuration::GlideRatio:
        case Configuration::InverseGlideRatio:
            return valueInUnits * 100;
        default:
            return valueInUnits;
        }
    case Configuration::ValueChange:
        return valueInUnits * 100;
    default:
        return valueInUnits;
    }
}

bool operator==(
        const Configuration &a,
        const Configuration &b)
{
    if (a.model != b.model) return false;
    if (a.rate  != b.rate)  return false;


    if (a.toneMode != b.toneMode) return false;
    if (a.minTone != b.minTone) return false;
    if (a.maxTone != b.maxTone) return false;
    if (a.limits != b.limits) return false;
    if (a.toneVolume != b.toneVolume) return false;

    if (a.rateMode != b.rateMode) return false;
    if (a.minRateValue != b.minRateValue) return false;
    if (a.maxRateValue != b.maxRateValue) return false;
    if (a.minRate != b.minRate) return false;
    if (a.maxRate != b.maxRate) return false;
    if (a.flatline != b.flatline) return false;

    if (a.speechMode != b.speechMode) return false;
    if (a.speechUnits != b.speechUnits) return false;
    if (a.speechRate != b.speechRate) return false;
    if (a.speechDecimals != b.speechDecimals) return false;
    if (a.speechVolume != b.speechVolume) return false;

    if (a.vThreshold != b.vThreshold) return false;
    if (a.hThreshold != b.hThreshold) return false;

    if (a.adjustSpeed != b.adjustSpeed) return false;
    if (a.timeZoneOffset != b.timeZoneOffset) return false;

    if (a.initMode != b.initMode) return false;
    if (a.initFile != b.initFile) return false;

    if (a.alarmWindowAbove != b.alarmWindowAbove) return false;
    if (a.alarmWindowBelow != b.alarmWindowBelow) return false;
    if (a.groundElevation != b.groundElevation) return false;

    if (a.alarms.size() != b.alarms.size()) return false;
    for (int i = 0; i < a.alarms.size(); ++i)
    {
        if (a.alarms[i].elevation != b.alarms[i].elevation) return false;
        if (a.alarms[i].mode != b.alarms[i].mode) return false;
        if (a.alarms[i].file != b.alarms[i].file) return false;
    }

    if (a.windows.size() != b.windows.size()) return false;
    for (int i = 0; i < a.windows.size(); ++i)
    {
        if (a.windows[i].top != b.windows[i].top) return false;
        if (a.windows[i].bottom != b.windows[i].bottom) return false;
    }

    return true;
}
