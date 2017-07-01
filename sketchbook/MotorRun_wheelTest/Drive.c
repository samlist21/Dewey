#include "dewey.h"
#include "<math.h>"


void PDController_base(dewey, time)
Dewey * dewey;
double time;
{
  double Fx, Mz, PDBase_translate(), PDBase_rotate();

  Fx = PDBase_translate(roger, time);
  Mz = PDBase_rotate(roger, time);

  // integrated wheel torque control
  dewey->wheel_torque[LEFT] = Fx / 2 - Mz / (2 *  R_AXLE);
  dewey->wheel_torque[RIGHT] = Fx / 2 + Mz / (2 *  R_AXLE);

}

double PDBase_translate(dewey, time) 
Dewey * dewey;
double time;
{   
  double r_x = dewey->base_setpoint[X] - dewey->base_position[X];
  double r_y = dewey->base_setpoint[Y] - dewey->base_position[Y];
  
  double error_trans = r_x * cos(dewey->base_setpoint[THETA]) + r_y * sin(dewey->base_setpoint[THETA]);
  double Fx = kp_base_trans * (error_trans) - kd_base_trans *((dewey->base_velocity[X] * cos(dewey->base_position[THETA]) + dewey->base_velocity[Y] * sin(dewey->base_position[THETA])));

  return(Fx);
}

double PDBase_rotate(dewey, time) 
Dewey * dewey;
double time;
{
  double Mz = kp_base_rot * (roger->base_setpoint[THETA] - roger->base_position[THETA]) - kd_base_rot * roger->base_velocity[THETA];

  return(Mz);
}
