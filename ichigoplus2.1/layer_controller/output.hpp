//libraries
#ifndef OUTPUT_HPP_INCLUDED
#define OUTPUT_HPP_INCLUDED
//application

//controller

//base
#include "system.h"
#include "mcutime.h"
#include "layer_controller/SelfPosition.hpp"

//board
#include "pin.hpp"
#include "layer_driver/circuit/can_encoder.hpp"
#include<math.h>
//circuit

class Output{
public:

    Digital *a[3];
    Digital *b[3];
    Pwm *c[3];
	int i=0;
	int w=0;
	float q;
	float sa=0;
	float g=2,radgs=3;
	float lp,om1=0,om2=0,om3=0,re=16,n,k;
	float la,r=10;
	Output(CW0 &a0,CCW0 &b0,Pwm0 &c0,CW1 &a1,CCW1 &b1,Pwm1 &c1,CW2 &a2,CCW2 &b2,Pwm2 &c2);
	void put(float m[]);
};

#endif // SPEAD_HPP_INCLUDED
