#include "dipan.hpp"
#include <math.h>
#define MAX(a,b) ((a)>(b)?(a):(b))
void DIPAN::jiesuan(void)
{
    v_1 = -(w*216.91+sqrt(2)/2*v_y+sqrt(2)/2*v_x)/77.86f;//左前，单位：转速
    v_2 = -(w*216.91-sqrt(2)/2*v_y+sqrt(2)/2*v_x)/77.86f;//左后
    v_3 = -(w*216.91-sqrt(2)/2*v_y-sqrt(2)/2*v_x)/77.86f;//右后
    v_4 = -(w*216.91+sqrt(2)/2*v_y-sqrt(2)/2*v_x)/77.86f;//右前
    v_1 = v_1*60*15;
    v_2 = v_2*60*15;
    v_3 = v_3*60*15;
    v_4 = v_4*60*15;
    float v_max = 0;
    float max_v = 300*15;
    v_max = MAX(MAX(MAX(abs(v_1),abs(v_2)),abs(v_3)),abs(v_4));
    if(v_max > 300 * 15)
    {
        v_1 = v_1/v_max*max_v;
        v_2 = v_2/v_max*max_v;
        v_3 = v_3/v_max*max_v;
        v_4 = v_4/v_max*max_v;
    }
}