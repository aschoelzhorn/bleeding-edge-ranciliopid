#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

#include <ADS1X15.h>

class PressureSensor {
   
public:
    PressureSensor();

    void initPressureSensor(void);
    float getPressure(void);
    bool isPressureSensorWorking(void);

private:
    bool m_isWorking;
    float m_previousPressure;
    float m_currentPressure;
    ADS1115* m_ads1115;
};

#endif
