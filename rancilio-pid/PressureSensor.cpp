#include "PressureSensor.h"
#include "rancilio-debug.h"
#include "ADS1X15.h"
#include <Arduino.h>
#include <Wire.h>


// #ifdef ESP32
//     Wire1.begin(PRESSURE_SENSOR_SDA, PRESSURE_SENSOR_SCL);
//     ADS1115 ADS(0x48, &Wire1);
// #else
//     ADS1115 ADS(0x48);
// #endif

PressureSensor::PressureSensor() {
#ifdef ESP32
    Wire1.begin(PRESSURE_SENSOR_SDA, PRESSURE_SENSOR_SCL);
    m_ads1115 = new ADS1115(0x48, &Wire1);
#else
    m_ads1115 = new ADS1115(0x48);
#endif
    m_isWorking = false;
}

void PressureSensor::initPressureSensor() {
    if (m_ads1115->begin()) {
        ERROR_println("Pressure sensor cannot be initialized");
        m_isWorking = false;
    }
    m_ads1115->setGain(0);      // 0 = default = 6.144 volt
    m_ads1115->setDataRate(4);  // 4 = default = fast, 0 = slowest, 7 = fastest
    m_ads1115->setMode(0);      // continuous mode
    m_ads1115->readADC(0);      // first read to trigger
    m_isWorking = true;
}

bool PressureSensor::isPressureSensorWorking() {
    return m_isWorking;
}

// from spec: Output signal 0.5-4.5V, Input 5V-12V

  float pressureZero = 2666.7; // voltageZero = 0.5V --> 25.6 (8 bit) or 102.4 (10 bit) or 2666.7 (ADS 15 bit)
  float pressureMax = 24000;   // voltageMax = 4.5V --> 230.4 (8 bit) or 921.6 (10 bit) or 24000 (ADS 15 bit)
  float range = pressureMax - pressureZero; // = 21333.3 for ADS 15 bit
  int maxBar = 12;
  float divider = range / maxBar; // = 1777.8 for ADS 15 bit

float PressureSensor::getPressure() {
    uint16_t value = 0;
    value = m_ads1115->getValue();

    m_previousPressure = m_currentPressure;
    m_currentPressure = (value - pressureZero) / divider;

    return m_currentPressure;
}
