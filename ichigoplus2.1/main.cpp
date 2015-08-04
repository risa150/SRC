//libraries

//application

//controller

//base
#include "system.h"
#include "mcutime.h"

//board
#include "pin.hpp"
#include<math.h>
//#define M_PI 3.141592
//circuit

class KG {
public:
	int l=90,d=40,f=200,hn[3];
	int oenc0=0,oenc1=0,oenc2=0;
	float radgs=2;
	float g=3;
	float gs=3; //x,yの誤差

	float a=30;	//α：30　β：30
	float b=-90;//α：-90 β：150
	float c=150;//α：150　β：-90
	float aang,bang,cang;
	float nas,nbs,ncs,nase,nbse,ncse,abx,aby,bcx,bcy,acx,acy,avex,avey;
	float adist,bdist,cdist,ax,bx,cx,ay,by,cy,asl,bsl,csl,ase,bse,cse;
	int p,j=0;
	float xa[7]={0,-130,0,-500,0,630,0};  //-500:hidari
	float ya[7]={2000,-130,500,0,-500,-2000+130,0};  //-500:sita
	float lp,om1=0,om2=0,om3=0,re=16,n,k;
	float deg=0,rad=0,q,m1=0,m2=0,m3=0,sa=0,w=0;
	float la,r=10;
	int time=0;
    KG();
    void timer();
    void jkit();
    void angle();
    void out();
    Serial0 serial;

    Sw0 s0;
    Sw1 s1;
    Sw2 s2;
    Sw3 s3;
    CW0 a0;
    CCW0 b0;
   	Pwm0 c0;
   	CW1 a1;
   	CCW1 b1;
   	Pwm1 c1;
	CW2 a2;
    CCW2 b2;
    Pwm2 c2;
    Enc0 enc0;
    Enc1 enc1;
    Enc2 enc2;

};

KG::KG(){
	c0.setupPwmOut(10000,0);
	c1.setupPwmOut(10000,0);
	c2.setupPwmOut(10000,0);
	s0.setupDigitalIn();
	s1.setupDigitalIn();
	s2.setupDigitalIn();
	s3.setupDigitalIn();
	a0.setupDigitalOut();
	a1.setupDigitalOut();
	a2.setupDigitalOut();
	b0.setupDigitalOut();
	b1.setupDigitalOut();
	b2.setupDigitalOut();
	serial.setup(115200);
	enc0.setup();
	enc1.setup();
	enc2.setup();

	a+=90;
	b+=90;
	c+=90;
	a=a/180*M_PI;
	b=b/180*M_PI;
	c=c/180*M_PI;
}

void KG::timer(){
	if(millis()-time>50){
		time=millis();
		out();
	}
}
void KG::jkit(){
	aang=a;	//0.5
	bang=b;	//0.6
	cang=c;	//0.6

	adist=((float)enc0.count()-(float)oenc0)/f*d*M_PI;  /*距離*/
	bdist=((float)enc1.count()-(float)oenc1)/f*d*M_PI;
	cdist=((float)enc2.count()-(float)oenc2)/f*d*M_PI;

	ax=cos(aang)*adist;
	ay=sin(aang)*adist;
	bx=cos(bang)*bdist;
	by=sin(bang)*bdist;
	cx=cos(cang)*cdist;
	cy=sin(cang)*cdist;

	if(aang==M_PI||aang==0){
		asl=0;
		hn[0]=1;
	}
	else{
		hn[0]=0;
		asl=(tan(aang));
		nas=(-1/asl);
		nase=-nas*ax+ay;
	}
	if(bang==M_PI || bang==0){
		bsl=0;
		hn[1]=1;
	}
	else{
		bsl=(tan(bang));
		nbs=(-1/bsl);
		nbse=(-nbs*bx+by);
		hn[1]=0;
	}
	if(cang==M_PI || cang==0){
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
		if(ya[j]!=0)
			k=(ya[j]/fabs(ya[j]))*M_PI/2;
		else
			k=0;
	}

	la=sqrt(pow(avex,2)+pow(avey,2));

	avex=cos(k+rad)*la;
	avey=sin(k+rad)*la;

	xa[j]-=avex;
	ya[j]-=avey;
	if(fabs(xa[j])<gs&&fabs(ya[j])<gs)
		j++;
	if(xa[j]==0&&ya[j]==0){
		c0.pwmWrite(1);
		c1.pwmWrite(1);
		c2.pwmWrite(1);
	}
}

void KG::angle(){
	rad+=(adist+bdist+cdist)/3/l;
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
}

void KG::out(){

	if(xa[j]!=0){
		sa=atan(ya[j]/xa[j]);
	if(ya[j]>0&&xa[j]<0)
	    sa+=M_PI;
	if(ya[j]<0&&xa[j]<0)
	    sa+=M_PI;
	}
	else if(ya[j]!=0)
	   	sa=(ya[j]/fabs(ya[j]))*M_PI/2;
	else
		sa=0;

	m1=cos(sa-(a+rad));
	m2=cos(sa-(b+rad));
	m3=cos(sa-(c+rad));

	jkit();
	angle();

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

    if(fabs(deg)>radgs){
    	n=sin(rad/2)*g;    //調節必要
    	m1-=n;
    	m2-=n;
    	m3-=n;
    }

    if(m1>0){
      a0.digitalWrite(0);
      b0.digitalWrite(1);
    }
    else{
      a0.digitalWrite(1);
      b0.digitalWrite(0);
    }
    if(m2>0){
      a1.digitalWrite(0);
      b1.digitalWrite(1);
   	}
    else{
    	a1.digitalWrite(1);
    	b1.digitalWrite(0);
    }
    if(m3>0){
    	a2.digitalWrite(0);
    	b2.digitalWrite(1);
    }
    else{
     	a2.digitalWrite(1);
     	b2.digitalWrite(0);
    }

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
    lp=sqrt(pow(xa[j],2)+pow(ya[j],2));
 	if(lp/100<1){
 		m1*=(lp/100);
   		m2*=(lp/100);
   		m3*=(lp/100);
 	}

	c0.pwmWrite((1-(om1+((fabs(m1*re)-fabs((float)enc0.count()-(float)oenc0))/r))));
	c1.pwmWrite((1-(om2+((fabs(m2*re)-fabs((float)enc1.count()-(float)oenc1))/r))));
	c2.pwmWrite((1-(om3+((fabs(m3*re)-fabs((float)enc2.count()-(float)oenc2))/r))));

	om1=om1+(fabs(m1*re)-fabs((float)enc0.count()-(float)oenc0))/r;
	om2=om2+(fabs(m2*re)-fabs((float)enc1.count()-(float)oenc1))/r;
	om3=om3+(fabs(m3*re)-fabs((float)enc2.count()-(float)oenc2))/r;

	serial.printf("%.2f  %.2f  %.2f  %.2f %.2f  %.2f  %.2f  %.2f  %.2f\n\r",m1*re,m2*re,m3*re,sa*180/M_PI,deg,k*180/M_PI,avex,avey);

	oenc0=enc0.count();
	oenc1=enc1.count();
	oenc2=enc2.count();
	serial.printf("%f\t,%f\t,%f\t\n\r",avex,avey,ya[j]);

}

int main(void)
{
	KG kg;
	while(1){
		kg.serial.printf("hello\r\n");
	if(kg.s0.digitalRead()==0){
	    while(kg.s3.digitalRead()==1){
	    	kg.timer();
	    }
	    	kg.c0.pwmWrite(1);
	    	kg.c1.pwmWrite(1);
	    	kg.c2.pwmWrite(1);
	    }

	}

	return 0;

}
