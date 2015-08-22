//libraries

//application

//controller

//base
#include "system.h"
#include "mcutime.h"
#include "layer_controller/SelfPosition.hpp"
#include "layer_controller/Angle.hpp"
//board
#include "pin.hpp"
#include "layer_driver/circuit/can_encoder.hpp"
#include<math.h>
//circuit

void Angle::getangle(float rad){
	deg=rad*180/M_PI;
	m1=0;
	m2=0;
	m3=0;
	if(fabs(deg)>radgs){
    	n=sin(rad/2)*g;    //’²ß•K—v
    	if(fabs(n)>max)n=n/fabs(n)*max;
    	if(fabs(n)<min&&fabs(rad*180/M_PI)>deggs)n=n/fabs(n)*min;
    	m1-=n;
    	m2-=n;
    	m3-=n;
    }
}
