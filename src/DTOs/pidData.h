#pragma once

struct PidData {
    int mode;
    double input;    // temperature
    double output;   // output
    double setpoint; // setpoint
    double kd;
    double kp;
    double ki;
};