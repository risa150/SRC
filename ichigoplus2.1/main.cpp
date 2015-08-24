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
#include "layer_controller/spead.hpp"//speed
#include "layer_controller/Angle.hpp"
#include "pin.hpp"
#include "layer_driver/circuit/can_encoder.hpp"
#include<math.h>

//circuit




int main(void)
{
	int timer=0;

	//float xa[]={    0,    0,    0, -900,    0,    0,    0,  900,    0,    0,    0,-1400,   0,    0,    0, 1750,    0,    0,    0,    0,    0}; 	 //-500:hidari
	//float ya[]={ 1400,    0, -200, -600, -700,    0,  400,  800,  200,    0, -400, -200,-900,    0,  500,  200,  500,    0, -900,    0,    0};  //-500:sita ookubo:1550
	//–ž• Žž							ªx-900~950

	//red
//	float xa[]={    0,    0,    0,-1400,   0,    0,    0, 1800,    0,    0,    0, -650,    0,    0,    0,  900,    0,    0,    0,    0,    0}; 	 //-500:hidari
//	float ya[]={ 1400,    0, -400, -200,-900,    0,  500,  100,  800,    0, -200, -350, -700,    0,  400,  800,  200,    0, -900,    0,    0};  //-500:sita ookubo:1550

	//blue
	float xa[]={    0,    0,    0,-1400,   0,    0,    0, 1800,    0,    0,    0, -650,    0,    0,    0,  900,    0,    0,    0,    0,    0}; 	 //-500:hidari
	float ya[]={ 1400,    0, -400, -200,-900,    0,  500,  100,  800,    0, -200, -350, -700,    0,  400,  800,  200,    0, -900,    0,    0};  //-500:sita ookubo:1550

	int i;
	float m[3]={0};
	int armcou=0;
	int ltimer=0;
	float candeg[3]={90,-30,-150};
	float zkdkdeg[3]={30,150,-90};
	int resttimer=0;
	float deggs=2;
	Can0 can;
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
    CW3 a3;
    CCW3 b3;
    Pwm3 c3;
    Enc0 zkdkenc0;
    Enc1 zkdkenc1;
    Enc2 zkdkenc2;
    A0 g;
    A1 limb;
    A3 limf;
    A4 armPtt;
    Led0 led;

    limb.setupDigitalInPullDown();
    limf.setupDigitalInPullDown();
    armPtt.setupAnalogIn();
    led.setupDigitalOut();
    g.setupDigitalInPullDown();
    zkdkenc0.setup();
    zkdkenc1.setup();
    zkdkenc2.setup();
	c0.setupPwmOut(10000,1);
	c1.setupPwmOut(10000,1);
	c2.setupPwmOut(10000,1);
	c3.setupPwmOut(10000,1);
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
	a3.setupDigitalOut();
	b3.setupDigitalOut();
	serial.setup(115200);
	CanEncoder enc0(can,3,5);				//65535
	CanEncoder enc1(can,1,5);
	CanEncoder enc2(can,2,5);

	enc0.setup();
	enc1.setup();
	enc2.setup();
	enc0.cpr(200);		//ƒKƒ“ƒ}
	enc1.cpr(200);
	enc2.cpr(1000);
	/*enc0.cpr(400);		//ƒ¿
	enc1.cpr(1000);
	enc2.cpr(200);
	enc0.rev(true);
	enc1.rev(false);
	enc2.rev(true);*/
	float machineAngle=0;
	int j=0;
	float m1,m2,m3;
	float gs=5;
	float oenc0=0,oenc1=0,oenc2=0;
	Buzzer pfpf;
	pfpf.setupDigitalOut();
	Angle angl;
	Out out;
	SelfPosition slfps(enc0,enc1,enc2);
	Output oput(a0,b0,c0,a1,b1,c1,a2,b2,c2);
	Speed spe(zkdkenc0,zkdkenc1,zkdkenc2);

	slfps.setup(candeg);
	out.setup(zkdkdeg);
	/*x[10]=30;
	y[10]=30;*/
	//slfps.getposition();
	//À•W‚©‚çslfps.machinex,y‚ð‚Ð‚­

	//slfps.getposition();

	//serial.printf("%f  %f\r\n",xa[j],ya[j]);
	pfpf.digitalLow();
	c3.pwmWrite(1);
	int choice=1;
	while(choice==1){
	if(s1.digitalRead()==0){
		if(j==0)choice=0;
		j=0;
		wait(300);
	}
	if(s2.digitalRead()==0){
		if(j==6)choice=0;
		j=6;
		wait(300);
	}
	if(s3.digitalRead()==0){
		if(j==13)choice=0;
		j=13;
		wait(300);
	}
	}
	while(1){
			slfps.oenc0=enc0.count();
			slfps.oenc1=enc1.count();
			slfps.oenc2=enc2.count();
			//if(enc0.count()!=0||enc1.count()!=0||enc2.count()!=0)
			serial.printf("hello\r\n");
			if(s1.digitalRead()==0){
				wait(100);
				if(s1.digitalRead()==0){
				if(armcou==0){
					armcou=1;
					a3.digitalWrite(0);
					b3.digitalWrite(1);
					c3.pwmWrite(0);
					while(limb.digitalRead()==0);
					wait(50);
					while(limb.digitalRead()==0);
					c3.pwmWrite(1);
				}
				else{
					armcou=0;
					a3.digitalWrite(1);
					b3.digitalWrite(0);
					c3.pwmWrite(0);
					while(limf.digitalRead()==0);
					wait(50);
					while(limf.digitalRead()==0);
					c3.pwmWrite(1);
				}
				}
			}
			if(s2.digitalRead()==0){
				while(1){
				if(millis()-ltimer>300){
					ltimer=millis();
					g.digitalToggle();
				}
				if(millis()-timer>50){
					timer=millis();
				slfps.getposition();

				if(fabs(xa[j])<gs&&fabs(ya[j])<gs){
					xa[j]=0;
					ya[j]=0;
					if(slfps.rad*180/M_PI<deggs){
					c0.pwmWrite(1);
					c1.pwmWrite(1);
					c2.pwmWrite(1);
					j++;
				if(xa[j]==0&&ya[j]==0){
					j++;
					if(armcou==0){
						armcou=1;
						a3.digitalWrite(0);
						b3.digitalWrite(1);
						c3.pwmWrite(0);
						while(limb.digitalRead()==0);
						wait(50);
						while(limb.digitalRead()==0);
						c3.pwmWrite(1);
						slfps.rad=0;
						resttimer=millis();
						while(millis()-resttimer<4000){
								slfps.oenc0=enc0.count();
								slfps.oenc1=enc1.count();
								slfps.oenc2=enc2.count();
						}
					}
					else{
						armcou=0;
						a3.digitalWrite(1);
						b3.digitalWrite(0);
						c3.pwmWrite(0);
						while(limf.digitalRead()==0);
						wait(50);
						while(limf.digitalRead()==0);
						c3.pwmWrite(1);
					}

				if(xa[j]==0&&ya[j]==0){
					pfpf.digitalHigh();
					c0.pwmWrite(1);
					c1.pwmWrite(1);
					c2.pwmWrite(1);
					while(1){
						if(millis()-ltimer>300){
							ltimer=millis();
							g.digitalToggle();
						}
					}
				}
				}
				}
				}
				xa[j]-=slfps.avex;
				ya[j]-=slfps.avey;

				out.getidealangle(xa[j],ya[j],slfps.rad);

				angl.getangle(slfps.rad);
			    m1=out.m1+angl.m1;
				m2=out.m2+angl.m2;
				m3=out.m3+angl.m3;
				/*m1=out.m1;
				m2=out.m2;
				m3=out.m3;//*/
				/*m1=out.m1;
				m2=out.m2;
				m3=out.m3;//*/
				/*m1=angl.m1;
				m2=angl.m2;
				m3=angl.m3;//*/

				spe.getspeed(out.m1,out.m2,out.m3,ya[j],xa[j],angl.m1);
				m[0]=m1;
				m[1]=m2;
				m[2]=m3;
				oput.put(m);
				//serial.printf("%f  %f  %f  %f  %f  %f  %f\r\n",angl.m1,angl.m2,angl.m3,out.m1,out.m2,out.m3,slfps.deg);
			serial.printf("%f  %f  %d  %d  %d  %f\n\r",xa[j],ya[j],enc0.count(),enc1.count(),enc2.count(),slfps.deg);
			}
		}
			}
	}

	return 0;
}
