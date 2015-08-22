//libraries

//application

//controller

//base
#include "system.h"
#include "mcutime.h"

//board
#include "layer_controller/SelfPosition.hpp"
#include "layer_controller/out.hpp"
#include "pin.hpp"
#include "layer_driver/circuit/can_encoder.hpp"
#include<math.h>

//circuit

void Out::setup(float deg[]){
	int i=0;
	for(i=0;i<3;i++){
		this->deg[i]=(deg[i]+90)/180*M_PI;
	}
	a=this->deg[0];
	b=this->deg[1];
	c=this->deg[2];
}

void Out::getidealangle(float xa,float ya,float rad){
	rad=0;
	if(xa!=0){
			sa=atan(ya/xa);
		if(ya>0&&xa<0)
			sa+=M_PI;
		if(ya<0&&xa<0)
			sa+=M_PI;
	}
		else if(ya!=0)
			sa=(ya/fabs(ya))*M_PI/2;
		else
			sa=0;

		m1=cos(sa-(a+rad));
		m2=cos(sa-(b+rad));
		m3=cos(sa-(c+rad));

		w=fabs(m1);
		if(w<fabs(m2))
			w=fabs(m2);
		if(w<fabs(m3))
			w=fabs(m3);
		if(w!=0){
			m1/=w;
			m2/=w;
			m3/=w;
		}

}
