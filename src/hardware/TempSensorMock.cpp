/**
 * @file TempSensorMock.cpp
 *
 * @brief Handler for temperature sensor mock for testing without hardware
 */

#include "TempSensorMock.h"
#include "Logger.h"
#include <Arduino.h>

TempSensorMock::TempSensorMock(int function) {
    function_ = function;
}

unsigned long previousMillis = 0;
float temp_current = 27;

float getTemperature(float maxValue) {

    if (temp_current > maxValue) {
        return maxValue;
    }

    unsigned long now = millis();
    if (now - previousMillis >= 1000ul) {
        temp_current += 1.3;
        previousMillis = now;
    }
   
    LOGF(TRACE, "temp_current = %.1f", temp_current);
    return temp_current;
}

bool TempSensorMock::sample_temperature(double& temperature) const {
    if (function_ == 1) { // steam
        temperature = getTemperature(117.0);
        return true;
    } else if (function_ == 2) { // error not heating
        temperature = 24;
        return false;
    } else if (function_ == 3) { // error too hot
        temperature = getTemperature(140.0);
        return false;
    } else { // normal
        temperature = getTemperature(95.0);
        return true;
    }
}
