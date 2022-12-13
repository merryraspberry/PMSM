#include "PI.h"


void PI_Init(struct PI *pid, float kp, float ki, float min, float max, float Ts) {
	pid->kp = kp;
	pid->ki = ki;
	pid->min = min;
	pid->max = max;
	pid->Ts = Ts;
	pid->a = 0;
	pid->b = 0;
	pid->b1 = 0;
	pid->c = 0;
	pid->c1 = 0;
	pid->d = 0;
	pid->e = 0;
	pid->x = 0;
	pid->x1 = 0;
	pid->y = 0;
	pid->y1 = 0;
}

void PI_Calc(struct PI *pid, float x) {
	pid->x = x;

	pid->y = (pid->x * pid->kp) + ((pid->x * pid->ki * pid->Ts) / 2) - (pid->x1 * pid->kp) + ((pid->x1 * pid->ki * pid->Ts) / 2) + pid->y1;

	if(pid->y>pid->max){
		pid->y = pid->max;
		}
	if(pid->y<pid->min){
		pid->y = pid->min;
		}

	pid->x1 = pid->x;
	pid->y1 = pid->y;
}