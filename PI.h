struct PI {
	float kp;
	float ki;
	float min;
	float max;
	float Ts;
	float x;
	float y;
	float y1;
	float x1;
	float a;
	float b;
	float b1;
	float c;
	float c1;
	float d;
	float e;
};

struct PI PI_i_q;
struct PI PI_w;
struct PI PI_i_d;

void PI_Init(struct PI* pid , float kp, float ki, float min, float max, float Ts);
void PI_Calc(struct PI* pid , float x);