//libraries
#ifndef OUT_HPP_INCLUDED
#define OUT_HPP_INCLUDED
//application

//controller

//base
#include "system.h"
#include "mcutime.h"

//board
#include "layer_controller/SelfPosition.hpp"
#include "pin.hpp"
#include "layer_driver/circuit/can_encoder.hpp"
#include<math.h>

//circuit

class Out{
public:
	float q;
	float m1=0,m2=0,m3=0;
	float sa=0;
	float w;
	float a,b,c;
	float deg[3]={0};

	void getidealangle(float xa,float ya,float rad);
	void setup(float deg[]);

};

#endif // SPEAD_HPP_INCLUDED
