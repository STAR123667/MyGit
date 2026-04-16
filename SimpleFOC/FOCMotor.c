//===========================
//创建日期：2025-2-10
//作    者：Merk Mao
//功    能：机械轴角度和电度角
//===========================
#include "MyProject.h"


/******************************************************************************/
float shaft_angle;//!< current motor angle
float electrical_angle;
float shaft_velocity;
float current_sp;
float shaft_velocity_sp;
float shaft_angle_sp;
DQVoltage_s voltage;
DQCurrent_s current;

TorqueControlType torque_controller;
MotionControlType controller;

float sensor_offset=0;   //似乎没用
float zero_electric_angle;
/******************************************************************************/
// shaft angle calculation
float shaftAngle(void)
{
  // if no sensor linked return previous value ( for open loop )
  //if(!sensor) return shaft_angle;
  //return sensor_direction*getAngle() - sensor_offset;
#if M1_ABZ
	return sensor_direction*getAngle_ABZ() - sensor_offset;
#else
	return sensor_direction*getAngle() - sensor_offset;
#endif			
	
	
}
// shaft velocity calculation
float shaftVelocity(void)
{
  // if no sensor linked return previous value ( for open loop )
  //if(!sensor) return shaft_velocity;
  //return sensor_direction*LPFoperator(&LPF_velocity,getVelocity());
#if M1_ABZ
	return sensor_direction*LPFoperator(&LPF_velocity,getVelocity_ABZ());
#else
	return sensor_direction*LPFoperator(&LPF_velocity,getVelocity());
#endif		
	
	
	//return sensor_direction*getVelocity();
}
/******************************************************************************/
float electricalAngle(void)
{
  return _normalizeAngle((shaft_angle + sensor_offset) * pole_pairs - zero_electric_angle);
}
/******************************************************************************/


