#include "DllHeader.h"
#include "PI.h"
#include "transformations.h"
#include "math.h"
#define pi 3.141516

#define A_in aState->inputs[0]
#define B_in aState->inputs[1]
#define C_in aState->inputs[2]
#define fi aState->inputs[3]
#define w_ref aState->inputs[4]
#define wm aState->inputs[5]
#define id_ref aState->inputs[6]

#define A_out aState->outputs[0]
#define B_out aState->outputs[1]
#define C_out aState->outputs[2]

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
   aSizes->numInputs = 7;
   aSizes->numOutputs = 3;
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
	ABCdqInit(&ABCdq);
	dqABCInit(&dqABC);

	
		
}
void main(struct SimulationState* aState) {

	
	ABCdqCalc(&ABCdq, A_in, B_in, C_in, fi);

	PI_Calc(&PI_w, w_ref-wm);
	PI_Calc(&PI_i_d, id_ref - ABCdq.d);
	PI_Calc(&PI_i_q, PI_w.y - ABCdq.q );

	dqABCCalc(&dqABC, PI_i_d.y, PI_i_q.y, fi);
}


//This function is automatically called every sample time
//output is written to DLL output port after the output delay
DLLEXPORT void plecsOutput(struct SimulationState* aState)
{
	main(aState);
	A_out = dqABC.A;
	B_out = dqABC.B;
	C_out = dqABC.C;
}
