#include "DllHeader.h"
#include "PI.h"


#define x_d aState->inputs[0]
#define x_w aState->inputs[1]
#define i_q aState->inputs[2]

#define y_d aState->outputs[0]
#define y_q aState->outputs[1]

#define x1 aState->states[0]
#define y1 aState->states[1]


float kp_w = 0;
float ki_w = 0;

float kp_q = 0;
float ki_q = 0;

float kp_d = 0;
float ki_d = 0;

float Ts=0;
float sat=0;

float Imax = 0;
float Imin = 0;

DLLEXPORT void plecsSetSizes(struct SimulationSizes* aSizes)
{
   aSizes->numInputs = 3;
   aSizes->numOutputs = 2;
   aSizes->numStates = 2;
   aSizes->numParameters = 10; //number of user parameters passed in
}


//This function is automatically called at the beginning of the simulation
DLLEXPORT void plecsStart(struct SimulationState* aState)
{
	kp_w = aState->parameters[0];
	ki_w = aState->parameters[1];
	kp_d = aState->parameters[2];
	ki_d = aState->parameters[3];
	kp_q = aState->parameters[4];
	ki_q = aState->parameters[5];
	Ts = aState->parameters[6];
	sat = aState->parameters[7];
	Imin = aState->parameters[8];
	Imax = aState->parameters[9];
	
	PI_Init(&PI_w, kp_w, ki_w, Imin, Imax, Ts);
	PI_Init(&PI_i_d, kp_d, ki_d, -sat, sat, Ts);
	PI_Init(&PI_i_q, kp_q, ki_q, -sat, sat, Ts);

	
		
}
void main(struct SimulationState* aState) {

	PI_Calc(&PI_w, x_w);
	PI_Calc(&PI_i_d, x_d);
	PI_Calc(&PI_i_q, PI_w.y - i_q );
}


//This function is automatically called every sample time
//output is written to DLL output port after the output delay
DLLEXPORT void plecsOutput(struct SimulationState* aState)
{
	main(aState);
	y_d = PI_i_d.y;
	y_q = PI_i_q.y;
	
}
