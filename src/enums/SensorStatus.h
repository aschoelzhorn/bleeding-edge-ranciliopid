#ifndef SENSOR_STATUS_H
#define SENSOR_STATUS_H

#pragma once

// : 0 := OK, 1 := Hardware issue, 2:= Software issue / outlier detected, 3: temperature jump
enum class SensorStatus {
    Ok = 0,
    HardwareIssue = 1,
    SoftwareIssue = 2,
    TemperatureJump = 3
};

#endif
