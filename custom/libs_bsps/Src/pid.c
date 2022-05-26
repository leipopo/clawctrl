#include "main.h"


void PID_calc(PID_regulator *pid,float timetick)
{
	pid->err[0] = pid->err[1];
	pid->err[1] = pid->tar-pid->cur;
	
	pid->componentKp  = pid->kp*pid->err[1];
	pid->componentKi += pid->ki*pid->err[1]*timetick;
	pid->componentKd  = pid->kd*(pid->err[1]-pid->err[0])*timetick;
	
	pid->componentKp = LIMIT(pid->componentKp,-pid->componentKpMax,pid->componentKpMax);
	pid->componentKi = LIMIT(pid->componentKi,-pid->componentKiMax,pid->componentKiMax);
	pid->componentKd = LIMIT(pid->componentKd,-pid->componentKdMax,pid->componentKdMax);
	
	pid->output = pid->componentKp+pid->componentKi+pid->componentKd;
	pid->output = LIMIT(pid->output,-pid->outputMax,pid->outputMax);
}

void PID_angle_calc(PID_regulator *pid,float timetick,float angle_parameter)
{
	pid->err[0] = pid->err[1];
	pid->err[1] = pid->tar-pid->cur;
	if(pid->err[1]>angle_parameter)
		pid->err[1]-=360.f;
	else if(pid->err[1]<-angle_parameter)
		pid->err[1]+=360.f;
	
	pid->componentKp  = pid->kp*pid->err[1];
	pid->componentKi += pid->ki*pid->err[1]*timetick;
	pid->componentKd  = pid->kd*(pid->err[1]-pid->err[0])*timetick;
	
	pid->componentKp = LIMIT(pid->componentKp,-pid->componentKpMax,pid->componentKpMax);
	pid->componentKi = LIMIT(pid->componentKi,-pid->componentKiMax,pid->componentKiMax);
	pid->componentKd = LIMIT(pid->componentKd,-pid->componentKdMax,pid->componentKdMax);
	
	pid->output = pid->componentKp+pid->componentKi+pid->componentKd;
	pid->output = LIMIT(pid->output,-pid->outputMax,pid->outputMax);
}

void PID_clear(PID_regulator *pid)
{
	pid->err[0] = 0;
	pid->err[1] = 0;
	pid->componentKp = 0;
	pid->componentKi = 0;
	pid->componentKd = 0;
	pid->output = 0;
}

