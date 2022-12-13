struct ABCdq_struct {
	float A;
	float B;
	float C;
	float d;
	float q;
	float fi;
};

struct dqABC_struct {
	float A;
	float B;
	float C;
	float d;
	float q;
	float fi;
};

struct ABCdq_struct ABCdq;
struct dqABC_struct dqABC;

void ABCdqInit(struct ABCdq_struct* konv);
void ABCdqCalc(struct ABCdq_struct* konv, float A, float B, float C, float fi);

void dqABCInit(struct dqABC_struct* konv);
void dqABCCalc(struct dqABC_struct* konv, float d, float q, float fi);
