#ifndef DI_PAN_HPP
#define DI_PAN_HPP


class DIPAN{
public:
DIPAN(){};
void jiesuan(void);
void set_vel_gm(float rc_rv,float rc_rh)
{
    v_x = rc_rv * 1600;
    v_y = rc_rh * 1600;
}
float v_1 = 0;
float v_2 = 0;
float v_3 = 0;
float v_4 = 0;
private:
float v_x = 0;
float v_y = 0;
float w = 0;

};






#endif // DI_PAN_HPP