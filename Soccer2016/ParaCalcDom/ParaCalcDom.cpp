// ParaCalcDom.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include "ParaCalcDom.h"

ParaCalcDom::ParaCalcDom(Mat image, Players *pL, ConstNum *constNum, int time){
	img = image;
	NUM = constNum->getPointNUM()-1;
	LOOP = constNum->getLoop();
	scale = constNum->getScale();
	hspace = constNum->getSpace();
	wspace = constNum->getSpace();
	second = constNum->getSecond();
	EPS = constNum->getEPSILON();
	INFI = constNum->getINF();
	RE = constNum->getREPET();
	bRE = constNum->getBiREPET();
	VMax = constNum->getVMax();
	RESIST = constNum->getResist();
	cn = constNum;
	playersList = pL;
	moment = time;
	bb_mini = new CvPoint2D32f[NUM];
	bb_maxi = new CvPoint2D32f[NUM];
}

void ParaCalcDom::setBallReach(float *time){
	reachTime = time;
}

void ParaCalcDom::operator() (const blocked_range<int>& range) const{
//void operate(){
	int tx;
	float time=INFI;
	float t=0;
	float x2,y2;
	float vx,vy;
	float ex,ey;
	float resist = RESIST;
	float vmax = VMax;
	int agent=NUM;
	float ang;
	int width = cn->getFieldWidth()*cn->getScale()+2*cn->getSpace();
	int height = cn->getFieldHeight()*cn->getScale()+2*cn->getSpace();
	float *value = playersList->getValue();
	CvPoint2D32f *point = new CvPoint2D32f[NUM];
	CvPoint2D32f *point_t = new CvPoint2D32f[NUM];

	for(int i=range.begin();i<range.end();i++){
		point[i].x = playersList->getX()[i+moment*NUM];
		point[i].y = playersList->getY()[i+moment*NUM];
		point_t[i].x = playersList->getX()[i+(moment-1)*NUM];
		point_t[i].y = playersList->getY()[i+(moment-1)*NUM];
	}

	for(int i=range.begin();i<range.end();i++){
	//for(int i=1;i<NUM;i++){
		vx = VMax;		//速度のｘ成分
		vy = VMax;		//速度のｙ成分

		float dist = reachTime[i];

		float e = (float)(1-exp(-resist*dist))/resist;
		int pt1_x,pt1_y;
		int pt2_x,pt2_y;
		//以下修正が必要
		x2 = (float)(vmax*scale*(dist-e)+vx*e)*(vmax*scale*(dist-e)+vx*e);
		y2 = (float)(vmax*scale*(dist-e)+vy*e)*(vmax*scale*(dist-e)+vy*e);
		//tx = sqrt(x2+y2);
		t = sqrt(x2+y2);
		//vx = 0;
		//vy = 0;
		vx = (float)((point[i].x-point_t[i].x)/second);		//速度のｘ成分
		vy = (float)((point[i].y-point_t[i].y)/second);		//速度のｙ成分
		//float radius = (vmax+1)*scale*(fabs(dist-e)+fabs(e));
		float radius = (vmax+1)*scale*(dist-e);
		radius += sqrt(vx*vx+vy*vy)*e;

		pt1_x = (int)(point[i].x-radius);
		pt1_y = (int)(point[i].y-radius);
		pt2_x = (int)(point[i].x+radius);
		pt2_y = (int)(point[i].y+radius);
			
		if(pt1_x<wspace){
			pt1_x=wspace;
		}
		if(pt1_x>img.cols-wspace){
			pt1_x=img.cols-wspace;
		}
		if(pt1_y<hspace){
			pt1_y=hspace;
		}
		if(pt1_y>img.rows-hspace){
			pt1_y=img.rows-hspace;
		}
		if(pt2_x<wspace){
			pt2_x=wspace;
		}
		if(pt2_x>img.cols-wspace){
			pt2_x=img.cols-wspace;
		}
		if(pt2_y<hspace){
			pt2_y=hspace;
		}
		if(pt2_y>img.rows-hspace){
			pt2_y=img.rows-hspace;
		}
			
		bb_mini[i].x = pt1_x,bb_mini[i].y = pt1_y;
		bb_maxi[i].x = pt2_x,bb_maxi[i].y = pt2_y;

		//初期化
		for(int py = hspace-1;py <=img.rows-hspace+1;py++){
			for(int px=wspace-1; px<=img.cols-wspace+1; px++){
				*(value+i+NUM*(py+img.rows*px)) = INFI;
			}
		}

		for(int py=pt1_y;py<=pt2_y;py++){
			for(int px=pt1_x; px<=pt2_x; px++) {
				vmax = VMax;
				resist = RESIST;
				x2 = (float)((px-point[i].x)/second);
				y2 = (float)((py-point[i].y)/second);
				if(fabs(sqrt(vx*vx+vy*vy)*sqrt(x2*x2+y2*y2)) > 0){
					ang = (vx*x2+vy*y2)/(sqrt(vx*vx+vy*vy)*sqrt(x2*x2+y2*y2));
					//vmax = (1+(ang+1)/2)*vmax;
					//vmax = ((1-GAM)*(ang+1)/2+GAM)*vmax;
					vmax = VMax;
				}else{
					ang = 0;
					vmax = VMax;
				}
				x2 = (px-point[i].x);
				y2 = (py-point[i].y);
				ex = x2/sqrt(x2*x2+y2*y2);
				ey = y2/sqrt(x2*x2+y2*y2);
				//二分法
				float g_t,f_1=1,f_2=1,f_3,x_l=inita,x_r=initb,x_m;
				for(tx=0;tx<bRE;tx++){
					g_t = exp(-resist*x_l);
					g_t = (1-g_t)/resist;
					f_1 = vmax*scale*(x_l-g_t)*(vmax*scale*(x_l-g_t)+2*g_t*(vx*ex+vy*ey))+g_t*g_t*(vx*vx+vy*vy)-(x2*x2+y2*y2);
					g_t = exp(-resist*x_r);
					g_t = (1-g_t)/resist;
					f_2 = vmax*scale*(x_r-g_t)*(vmax*scale*(x_r-g_t)+2*g_t*(vx*ex+vy*ey))+g_t*g_t*(vx*vx+vy*vy)-(x2*x2+y2*y2);
					x_m = (x_l+x_r)/2;
					g_t = exp(-resist*x_m);
					g_t = (1-g_t)/resist;
					f_3 = vmax*scale*(x_m-g_t)*(vmax*scale*(x_m-g_t)+2*g_t*(vx*ex+vy*ey))+g_t*g_t*(vx*vx+vy*vy)-(x2*x2+y2*y2);
					if(f_1*f_2<=0){
						if(f_3*f_1>0){
							x_l = x_m;
						}else {
							x_r = x_m;
						}
						t = x_m;
						if(fabs(f_3)<EPS){
							break;
						}
					}else{
						//cout << "Exist points which can't compute." << endl;
					}
				}
				//二分法の終わり
				//割線法
				for(tx=0;tx < RE;tx++){
					g_t = exp(-resist*x_l);
					g_t = (1-g_t)/resist;
					f_1 = vmax*scale*(x_l-g_t)*(vmax*scale*(x_l-g_t)+2*g_t*(vx*ex+vy*ey))+g_t*g_t*(vx*vx+vy*vy)-(x2*x2+y2*y2);
					g_t = exp(-resist*x_r);
					g_t = (1-g_t)/resist;
					f_2 = vmax*scale*(x_r-g_t)*(vmax*scale*(x_r-g_t)+2*g_t*(vx*ex+vy*ey))+g_t*g_t*(vx*vx+vy*vy)-(x2*x2+y2*y2);
					f_3 = (x_r-x_l)/(f_2-f_1);
					x_m = x_r-f_2*f_3;
					if(fabs(f_2*f_3)<EPS){
						t = x_m;
						break;
					}else{
						x_l = x_r;
						x_r = x_m;
					}
				}
				//割線法の終わり
				//playersList->setValue(px, py, i, t);
				value[i+(py+px*img.rows)*NUM] = t;
				//cout << t << "	";
			}
		}
		//cout << "	" <<endl;
	}
	playersList->setValue(value);
	delete point_t;
	delete point;
}

void ParaCalcDom::dominantrect(int offense){
	CvScalar color;
	CvPoint p1,p2;
	int shift = 0;

	if(offense==1){
		shift = 1;
		color = CV_RGB(0,0,255);
	}else{
		shift = NUM/2+1;
		color = CV_RGB(255,0,0);
	}
	for(int i=shift;i<shift+NUM/2;i++){
		p1 = cvPointFrom32f(bb_mini[i]);
		p2 = cvPointFrom32f(bb_maxi[i]);
		//if(i==2)
		rectangle(img,p1,p2,color,1,CV_AA,0);
	}
}

CvPoint2D32f* ParaCalcDom::getBoundingBoxMin(){
	return(bb_mini);
}
CvPoint2D32f* ParaCalcDom::getBoundingBoxMax(){
	return(bb_maxi);
}

