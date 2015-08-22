//libraries
#ifndef SPEAD_HPP_INCLUDED
#define SPEAD_HPP_INCLUDED

//application

//controller

//base
#include "system.h"
#include "mcutime.h"

//board
#include "layer_controller/SelfPosition.hpp"
#include "layer_controller/out.hpp"
#include "layer_controller/output.hpp"
#include "pin.hpp"
#include "layer_driver/circuit/can_encoder.hpp"
#include<math.h>

//circuit

class Speed{
public:
	Encoder *enc0;
	Encoder *enc1;
	Encoder *enc2;
	float q,m1=0,m2=0,m3=0,sa=0,w=0;
	float ms[3]={0};
	float r=2;
	float rlm=20;
	int oenc[3]={0};
	float pwmsv[3]={0};
	//int oenc0=0,oenc1=0,oenc2=0;
	float lp,om1=0,om2=0,om3=0;
	void getspeed(float m1,float m2,float m3,float ya,float xa,float radm);
	Speed(Encoder &enc0,Encoder &enc1,Encoder &enc2);

};

#endif // SPEAD_HPP_INCLUDED
