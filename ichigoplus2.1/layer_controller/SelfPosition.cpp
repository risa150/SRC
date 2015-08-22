//libraries

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

SelfPosition::SelfPosition(Encoder &enc0,Encoder &enc1,Encoder &enc2){
	this->enc0=&enc0;
	this->enc1=&enc1;
	this->enc2=&enc2;
}

void SelfPosition::setup(float deg[]){
	int i=0;
	for(i=0;i<3;i++){
		candeg[i]=deg[i]+90;
	}
	a=candeg[0];
	b=candeg[1];
	c=candeg[2];
	pfpf.setupDigitalOut();
}

void SelfPosition::getposition(){
	if(fabs(enc0->count()-oenc0)>2000||fabs(enc1->count()-oenc1)>2000||fabs(enc2->count()-oenc2)>2000){
		//pfpf.digitalHigh();
		pf=1;
		//if((float)enc0->count()-oenc0>2000)
			oenc0=(float)enc0->count();
		//if((float)enc1->count()-oenc1>2000)
			oenc1=(float)enc1->count();
		//if((float)enc2->count()-oenc2>2000)
			oenc2=(float)enc2->count();
	}else{
		if(pf==1){
			pfpf.digitalLow();
			pf=0;
		}
		aang=a/180*M_PI;
		bang=b/180*M_PI;
		cang=c/180*M_PI;

		adist=((float)enc0->count()-oenc0)/enc0->cpr()*d*M_PI;  //‹——£  ƒKƒ“ƒ}
		bdist=((float)enc1->count()-oenc1)/enc1->cpr()*d*M_PI;
		cdist=((float)enc2->count()-oenc2)/enc2->cpr()*d*M_PI;

		oenc0=(float)enc0->count();
		oenc1=(float)enc1->count();
		oenc2=(float)enc2->count();

		/*adist=((float)enc0->count()*(-1)-oenc0)/enc0->cpr()*d*M_PI;  //‹——£  ƒ¿
		bdist=((float)enc1->count()-oenc1)/enc1->cpr()*d*M_PI;
		cdist=((float)enc2->count()*(-1)-oenc2)/enc2->cpr()*d*M_PI;

		oenc0=(float)enc0->count()*(-1);
		oenc1=(float)enc1->count();
		oenc2=(float)enc2->count()*(-1);*/
		ad+=adist;
		bd+=bdist;
		cd+=cdist;

		ax=cos(aang)*adist;
		ay=sin(aang)*adist;
		bx=cos(bang)*bdist;
		by=sin(bang)*bdist;
		cx=cos(cang)*cdist;
		cy=sin(cang)*cdist;

		if(a==180||a==0){
			asl=0;
			hn[0]=1;
		}
		else{
			hn[0]=0;
			asl=(tan(aang));
			nas=(-1/asl);
			nase=-nas*ax+ay;
		}
		if(b==180 || b==0){
			bsl=0;
			hn[1]=1;
		}
		else{
			bsl=(tan(bang));
			nbs=(-1/bsl);
			nbse=(-nbs*bx+by);
			hn[1]=0;
		}
		if(c==180 || c==0){
			csl=0;
			hn[2]=1;
		}
		else{
			csl=(tan(cang));
			cse=(-csl*cx+cy);
			ncs=(-1/csl);
			ncse=(-ncs*cx+cy);
			hn[2]=0;
		}
		//printf("%d  %d  %d",hn[0],hn[1],hn[2]);
		if(hn[0]==1||hn[1]==1){
			if(hn[0]==1){
				abx=ax;
				aby=nbs*abx+nbse;
			}else{
				abx=bx;
				aby=nas*abx+nase;
			}
		}else{
			abx=(nase-nbse)/(nbs-nas);
			aby=nas*abx+nase;
		}
		if(hn[1]==1||hn[2]==1){
			if(hn[1]==1){
				bcx=bx;
				bcy=ncs*bcx+ncse;
			}else{
				bcx=cx;
				bcy=nbs*bcx+nbse;
			}
		}else{
			bcx=(nbse-ncse)/(ncs-nbs);
			bcy=nbs*bcx+nbse;
		}
		if(hn[0]==1||hn[2]==1){
			if(hn[0]==1){
				acx=ax;
				acy=ncs*acx+ncse;
			}else{
				acx=cx;
				acy=nas*acx+nase;
			}
		}else{
			acx=(nase-ncse)/(ncs-nas);
			acy=nas*acx+nase;
		}

		avex=(abx+bcx+acx)/3;
		avey=(aby+bcy+acy)/3;
		if(avex!=0){
			k=atan(avey/avex);
		if(avey>0&&avex<0)
			k+=M_PI;
		if(avey<0&&avex<0)
			k+=M_PI;
		}
		else {
			if(avey!=0)
				k=(avey/fabs(avey))*M_PI/2;
			else
				k=0;
		}
		la=sqrt(pow(avex,2)+pow(avey,2));
		avex=cos(k+rad)*la;
		avey=sin(k+rad)*la;
		machineX+=avex;
		machineY+=avey;

		rad+=(adist+bdist+cdist)/3/l;
		//rad=0;
			deg=(rad*180/M_PI);
			p=deg/180;
			q=deg/180;

			if(p>0&&p!=q){
				if(p%2==0){
					deg=deg-p*180;
				}
				else{
					p++;
					deg=deg-180*p;
				}
			}
			else if(p<0&&p!=q){
				if(p%2==0){
					deg=deg-p*180;
				}
				else{
					p--;
					deg=deg-p*180;
				}
			}
			rad=deg/180*M_PI;
}
}
