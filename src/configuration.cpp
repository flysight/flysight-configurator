#include "configuration.h"

Configuration::Configuration()
{
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
