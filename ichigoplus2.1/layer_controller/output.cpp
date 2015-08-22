//libraries

//application

//controller

//base
#include "system.h"
#include "mcutime.h"
#include "layer_controller/SelfPosition.hpp"
#include "layer_controller/output.hpp"

//board
#include "pin.hpp"
#include "layer_driver/circuit/can_encoder.hpp"
#include<math.h>
//circuit



Output::Output(CW0 &a0,CCW0 &b0,Pwm0 &c0,CW1 &a1,CCW1 &b1,Pwm1 &c1,CW2 &a2,CCW2 &b2,Pwm2 &c2){
	this->a[0]=&a0;
	this->a[1]=&a1;
	this->a[2]=&a2;

	this->b[0]=&b0;
	this->b[1]=&b1;
	this->b[2]=&b2;

	this->c[0]=&c0;
	this->c[1]=&c1;
	this->c[2]=&c2;
}

void Output::put(float m[]){

	w=fabs(m[0]);
	for(i=1;i<3;i++){
		if(fabs(m[i])<w)
			w=fabs(m[i]);
	}
	if(w!=0){
		for(i=0;i<3;i++){
			m[i]/=w;
		}
	}
	for(i=0;i<3;i++){
		if(m[i]<0){
			a[i]->digitalWrite(1);
			b[i]->digitalWrite(0);
		}else{
			a[i]->digitalWrite(0);
			b[i]->digitalWrite(1);
		}
		c[i]->pwmWrite(1-fabs(m[i]));
	}
}

