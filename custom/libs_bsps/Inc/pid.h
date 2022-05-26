#ifndef __PID_H__
#define __PID_H__




#define PID_COMPONENT_NOLIMIT 60000
#define PID_OUTPUT_MAX_LIMIT  14000

typedef struct PID_regulator_t
{
	float tar;
	float cur;
	float err[2];
	float kp;
	float ki;
	float kd;
	float componentKp;
	float componentKi;
	float componentKd;
	float componentKpMax;
	float componentKiMax;
	float componentKdMax;
	float output;
	float outputMax;
}PID_regulator;

void PID_clear(PID_regulator *pid);
void PID_calc(PID_regulator *pid,float timetick);
void PID_angle_calc(PID_regulator *pid,float timetick,float angle_parameter);
#endif
