#include "transformations.h"
#include "math.h"
#define pi 3.141516

void ABCdqInit(struct ABCdq_struct* konv) {
	konv->A = 0;
	konv->B = 0;
	konv->C = 0;
	konv->d = 0;
	konv->q = 0;
	konv->fi = 0;
};

void dqABCInit(struct dqABC_struct* konv) {
	konv->A = 0;
	konv->B = 0;
	konv->C = 0;
	konv->d = 0;
	konv->q = 0;
	konv->fi = 0;
};

void ABCdqCalc(struct ABCdq_struct* konv, float A, float B, float C, float fi) {
	konv->A = A;
	konv->B = B;
	konv->C = C;
	konv->d = (2.0 / 3.0) * (cos(fi) * A + cos(fi - (2.0 / 3.0) * pi) * B + C * cos(fi + (2.0 / 3.0) * pi));
	konv->q = (2.0 / 3.0) * (-sin(fi) * A - B * sin(fi - (2.0 / 3.0) * pi) - sin(fi + (2.0 / 3.0) * pi) * C);
};
void dqABCCalc(struct dqABC_struct* konv, float d, float q, float fi) {
	konv->d = d;
	konv->q = q;
	konv->A = d * cos(fi) - q * sin(fi);
	konv->B = d * cos(fi - (2.0 / 3.0) * pi) - q * sin(fi - (2.0 / 3.0) * pi);
	konv->C = d * cos(fi + (2.0 / 3.0) * pi) - q * sin(fi + (2.0 / 3.0) * pi);
};