/*
 * @Author: rogue-wave zhangjingjie@zju.edu.cn
 * @Date: 2025-11-20 18:03:08
 * @LastEditors: rogue-wave zhangjingjie@zju.edu.cn
 * @LastEditTime: 2025-11-20 18:40:55
 * @FilePath: \dipan1_project\Tasks\dipan.hpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef DI_PAN_HPP
#define DI_PAN_HPP


class DIPAN{
public:
DIPAN(){};
void jiesuan(void);
void set_vel_gm(float rc_rv,float rc_rh)
{
    v_x = rc_rv * 400;
    v_y = rc_rh * 400;
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