//libraries
#ifndef SELFPOSITION_HPP_INCLUDED
#define SELFPOSITION_HPP_INCLUDED
//application

//controller

//base
#include "system.h"
#include "mcutime.h"

//board
#include "pin.hpp"
#include "layer_driver/circuit/can_encoder.hpp"
#include<math.h>

//circuit

class SelfPosition{
public:
	int l=115,d=30,hn[3];
	Encoder *enc0;
	Encoder *enc1;
	Encoder *enc2;
	float a,b,c;
	float ad=0,cd=0,bd=0;
	float oenc0=0,oenc1=0,oenc2=0;
	float deg=0;
	float aang,bang,cang;
	float nas,nbs,ncs,nase,nbse,ncse,abx,aby,bcx,bcy,acx,acy,avex,avey;
	float adist,bdist,cdist,ax,bx,cx,ay,by,cy,asl,bsl,csl,ase,bse,cse;
	float machineY=0;
	float machineX=0;
	float radgs=3;
	float g=2;
	float gs=5;
	float candeg[3]={0};
	int p,j=0,q;
	float k;
	float rad=0;
	float la,r=10;
	Buzzer pfpf;
	int pf=0;

		SelfPosition(Encoder &enc0,Encoder &enc1,Encoder &enc2);
		void setup(float deg[]);
		void getposition();

};

#endif // SPEAD_HPP_INCLUDED
