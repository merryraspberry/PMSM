#include "delay.h"

void delayInit(struct delay_struct* dl) {
	dl->d = 0;
	dl->q = 0;
	dl->d1 = 0;
	dl->q1 = 0;
	dl->d_out = 0;
	dl->q_out = 0;
};

void delayCalc(struct delay_struct* dl, float d, float q) {
	dl->d = d;
	dl->q = q;
	dl->d_out = dl->d1;
	dl->q_out = dl->q1;

	dl->d1 = dl->d;
	dl->q1 = dl->q;
}