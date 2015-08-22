//libraries
#ifndef ANGLE_HPP_INCLUDED
#define ANGLE_HPP_INCLUDED
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

class Angle{
public:
	float q;
	float deg;
	float m1=0,m2=0,m3=0,sa=0,w=0;
	float n,radgs=1,g=5;
	float deggs=5;
	float max=1;
	float min=0.3;
	void getangle(float rad);
};

#endif // SPEAD_HPP_INCLUDED
