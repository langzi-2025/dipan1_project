#include "pid.hpp"
void PID_::calc(void)
{
    integral += error;
    derivative = error - prev_error;
    output = kp * error + ki * integral + kd * derivative;
    if(max!=0)
    {
        if(output>max)
        {
            output = max;
        }
    }
    if(min!=0)
    {
        if(output<min)
        {
            output = min;
        }
    }
    prev_error = error;
}