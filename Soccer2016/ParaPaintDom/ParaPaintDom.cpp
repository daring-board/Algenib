// ParaPaintDom.cpp : DLL �A�v���P�[�V�����p�ɃG�N�X�|�[�g�����֐����`���܂��B
//

#include "stdafx.h"
#include "ParaPaintDom.h"

ParaPaintDom::ParaPaintDom(Mat image, Players *pList, ConstNum *cNum){
	img = image;
	playersList = pList;
	cn = cNum;
	NUM = cn->getPointNUM()-1;
	//NUM = NUM/2;
	INF = cn->getINF();
	width = cn->getFieldWidth()*cn->getScale()+2*cn->getSpace();
	hspace = cn->getSpace();
	wspace = cn->getSpace();
	dist = cn->getDist();
}

void ParaPaintDom::setBallReach(float *time){
	reachTime = time;
}
//�D���̈�̓h�蕪��
void ParaPaintDom::paint(int t){
	float tmp=cn->getINF(),time;
	int agent=0;
	int index=0;

	for(int py = hspace;py < img.rows-hspace;py++){
		for(int px = wspace; px < img.cols-wspace;px++) {  
			//for(int i = begin;i < end;i++){
			for(int i = 0;i < NUM-1;i++){
				//time = *(value+*(order+i)+NUM*(py+img->height*px));
				time = playersList->getValue()[i+(py+px*img.rows)*(NUM-1)];
				//cout<< time ;
				if(tmp >= time && time !=0){
					tmp = time;
					agent = i;
				}
			}
			index = agent;
			if(agent < (NUM-1)/2){
				agent = 0;
			}else{
				agent = 180;
			}
			color(px,py,agent,tmp,index);
			agent=0;
			tmp = cn->getINF();
		}
	}
}

void ParaPaintDom::operator() (const blocked_range<int>& range) const{
	float tmp=INF,time;
	int agent=0;
	int index=0;
	float *value = playersList->getValue();
		
	//for(int py = hspace;py < img->height-hspace;py++){
	for(int py = range.begin(); py < range.end(); py++){
		for(int px = wspace; px < width-wspace;px++) {  
			//for(int i = begin;i < end;i++){
			for(int i = 0;i < NUM;i++){
				time = value[i+(py+px*img.rows)*NUM];
				if(tmp >= time && time !=0){
					if(reachTime[i] > time){
						tmp = time;
						agent = i;
					}
				}
			}
			index = agent;
			if(agent < NUM/2){
				agent = 0;
			}else{
				agent = 180;
			}
			color(px,py,agent,tmp,index);			
			agent=0;
			tmp = INF;
		}
	}
}

//�e�I��̐F�����߂�iHSV��RGB�j
void ParaPaintDom::color(int px,int py,int agent,float time, int i) const{
	int a = img.step*py+(px*3);
	float H,V,S=0,F;
	int I,M,n,K;
	int flag=0;

//		if(agent == NUM || time > TIMES){	//���Ԃ�TIMES�b�őł��؂�
//			if(agent == NUM && time < TIMES){
	if(agent == NUM || time > reachTime[i]){	
		if(agent == NUM && time < reachTime[i]){

			V=255;S=1;
			flag=1;
		}else{
			V=255;S=1;
			flag=1;
		}
	}else if(agent>NUM/2){
		agent = agent-(NUM/2+1);
		V=250;
		S=0.7;
		V = V-100*time/dist;
		flag = 1;
		//V=250;S=1;
	}else{
		V=250;
		S=0.7;
		V = V-100*time/dist;
		//V=250;S=1;
	}
	if(flag==0){
		//srand(agent);
		//H = (float)(rand()%12)*30;
		H = (float)(agent);
		I = (int)H/60;
		F = H/60-I;
		M = (int)(V*(1-S));
		n = (int)(V*(1-S*F));
		K = (int)(V*(1-S*(1-F)));
		switch(I){
			case 0:
				img.data[a+2] = M;		//B����
				img.data[a+1] = K;		//G����
				img.data[a+0] = (int)V;		//R����
				break;
			case 1:
				img.data[a+2] = M;		//B����
				img.data[a+1] = (int)V;		//G����
				img.data[a+0] = n;		//R����
				break;
			case 2:
				img.data[a+2] = K;		//B����
				img.data[a+1] = (int)V;		//G����
				img.data[a+0] = M;		//R����
				break;
			case 3:
				img.data[a+2] = (int)V;		//B����
				img.data[a+1] = n;		//G����
				img.data[a+0] = M;		//R����
				break;
			case 4:
				img.data[a+2] = (int)V;		//B����
				img.data[a+1] = M;		//G����
				img.data[a+0] = K;		//R����
				break;
			case 5:
				img.data[a+2] = n;		//B����
				img.data[a+1] = M;		//G����
				img.data[a+0] = (int)V;		//R����
				break;
		}
	}else{
		//img->imageData[a+0] = 0;		//B����
		//img->imageData[a+1] = 200;		//G����
		//img->imageData[a+2] = 0;		//R����
	}
}
