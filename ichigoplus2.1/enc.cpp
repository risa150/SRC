//libraries

//application

//controller

//base
#include <stdio.h>


//board

#include<math.h>

//circuit


int main(void)
{

	int time=0;

	int i,l=90,d=40,f=200,p,hn[3],enc0=0,enc1=100,enc2=-100;
	float a=-90;
	float b=30;
	float c=150;
	float xa=0,ya=500;
    float aang,bang,cang,deg=0,rad,q,m1=0,m2=0,m3=0,sa=0,w=0;
	float adist,bdist,cdist,asl,bsl,csl,ase,bse,cse,ax,bx,cx,ay,by,cy;
	float nas,nbs,ncs,nase,nbse,ncse,abx,aby,bcx,bcy,acx,acy,avex,avey;

	a+=90;
	b+=90;
	c+=90;

	a=a/180*M_PI;
	b=b/180*M_PI;
	c=c/180*M_PI;

    while(1){
    	if(enc0!=0 || enc1!=0 || enc2!=0){
    		if(xa!=0)
    		sa=atan(ya/xa);
    		else
    		sa=(ya/fabs(ya))*M_PI/2;

    		m1=cos(sa-a);
    		m2=cos(sa-b);
    		m3=cos(sa-c);

    		aang=a;	//0.5
    		bang=b;	//0.6
    		cang=c;	//0.

    		ax=cos(aang)*enc0;
    		ay=sin(aang)*enc0;
    		bx=cos(bang)*enc1;
    		by=sin(bang)*enc1;
    		cx=cos(cang)*enc2;
    		cy=sin(cang)*enc2;


    		adist=((float)enc0/f)*d*M_PI;  /*‹——£*/
    		bdist=((float)enc1/f)*d*M_PI;
    		cdist=((float)enc2/f)*d*M_PI;

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

			rad=(adist+bdist+cdist)/3/l;
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
        //printf("%f  %f  %f\n",aby,bcy,acy);
        printf("%d,%d,%d,%f,%f\n\r",enc0,enc1,enc2,avex,avey);

    	}
    }
	return 0;
}

