struct delay_struct {
	float d;
	float q;
	float d_out;
	float q_out;
	float d1;
	float q1;
};

struct delay_struct delay1;

void delayInit(struct delay_struct* dl);
void delayCalc(struct delay_struct* dl, float d, float q);



