//libraries

//application

//controller

//base
#include "system.h"
#include "mcutime.h"

//board
#include "layer_controller/SelfPosition.hpp"
#include "layer_controller/out.hpp"
#include "layer_controller/output.hpp"
#include "layer_controller/spead.hpp"
#include "pin.hpp"
#include "layer_driver/circuit/can_encoder.hpp"
#include<math.h>
//#define M_PI 3.141592
//circuit

Speed::Speed(Encoder &enc0,Encoder &enc1,Encoder &enc2){
	this->enc0=&enc0;
	this->enc1=&enc1;
	this->enc2=&enc2;
}

void Speed::getspeed(float m1,float m2,float m3,float ya,float xa,float radm){
    float w=0;
	int i=0;
    w=fabs(m1);
    if(w<fabs(m2)){
       	w=fabs(m2);
     }
    if(w<fabs(m3)){
       	w=fabs(m3);
    }
    if(w!=0){
    	m1/=w;
    	m2/=w;
   	    m3/=w;
	}
    /*lp=sqrt(pow(xa,2)+pow(ya,2));
 	if(lp/100<1){
 		m1*=(lp/100);
   		m2*=(lp/100);
   		m3*=(lp/100);
 	}*/
 	ms[0]=m1+radm;
 	ms[1]=m2+radm;
 	ms[2]=m3+radm;
 	for(i=0;i<3;i++){
 		if(ms[i]!=0&&fabs(fabs(oenc[i])-fabs(enc0->count()))){
 			pwmsv[i]+=ms[i];
 			ms[i]+=pwmsv[i];
 		}else
 			pwmsv[i]=0;
 	}
	/*this->m1=(om1+((fabs(m1*re)-fabs((float)enc0->count()-(float)oenc0))/r));
	this->m2=(om2+((fabs(m2*re)-fabs((float)enc1->count()-(float)oenc1))/r));
	this->m3=(om3+((fabs(m3*re)-fabs((float)enc2->count()-(float)oenc2))/r));

	om1=om1+(fabs(m1*re)-fabs((float)enc0->count()-(float)oenc0))/r;
	om2=om2+(fabs(m2*re)-fabs((float)enc1->count()-(float)oenc1))/r;
	om3=om3+(fabs(m3*re)-fabs((float)enc2->count()-(float)oenc2))/r;*/

	oenc[0]=enc0->count();
	oenc[1]=enc1->count();
	oenc[2]=enc2->count();

}
