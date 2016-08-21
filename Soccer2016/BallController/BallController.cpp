// BallController.cpp : DLL �A�v���P�[�V�����p�ɃG�N�X�|�[�g�����֐����`���܂��B
//

#include "stdafx.h"
#include "BallController.h"

BallController::BallController(Ball *ball,Players *players, ConstNum *cn)
{
	LOOP = cn->getLoop();
	NUM = cn->getPointNUM()-1;
	shotBound = cn->getShotBound()*cn->getScale();
	angleBound = cn->getAngleBound();
	second = cn->getSecond();
	point = new CvPoint2D32f[LOOP];
	point_p = new CvPoint2D32f[LOOP*NUM];
	for(int i=0;i<LOOP;i++){
		point[i].x = ball->getX()[i];
		point[i].y = ball->getY()[i];
		for(int j=0;j<NUM;j++){
			point_p[j+i*NUM].x = players->getX()[j+i*NUM];
			point_p[j+i*NUM].y = players->getY()[j+i*NUM];
		}
	}
	EP = cn->getRadius()*cn->getScale();
	scale = cn->getSpace();
	MAXR = cn->getDist();
}

BallController::BallController(void)
{
	shotBound = 0.0f;
	angleBound = 0.0f;
	LOOP = 0;
	NUM = 0;
	EP = 0;
	second = 0.0f;
}

BallController::~BallController(void)
{
}

//�ߖT�ɂ���I��̏W���̏�����
void BallController::initneighbor(){
	stack<int> n_set();
}
//�{�[���̋ߖT�ɂ���I���index��ۑ�
void BallController::neighbor(int moment){
	int i;
	int counter=0;
	float x,x1,y,y1;

	x = point[moment].x;
	y = point[moment].y;
	for (i = 1; i < NUM; i++) {
		x1 = point_p[moment*NUM+i].x;
		y1 = point_p[moment*NUM+i].y;
		if(((x-x1)*(x-x1)+(y-y1)*(y-y1)) < EP*EP){
			//cout << i << ":";
			n_set.push(i);
		}
	}
	//cout << endl;
}
//�u��i�ɂ�����{�[���̑����Ԃ��B
float BallController::ballspeed(int i){
	float speed=0,vx,vy;
	if(i>=1){
		vx = (float)((point[i].x-point[(i-1)].x)/second);		//���x�̂�����
		vy = (float)((point[i].y-point[(i-1)].y)/second);		//���x�̂�����
		speed = sqrt(vx*vx+vy*vy);
	}else{
		//cout << "exception! BallSpeed" << endl;
		exit(0);
	}
	return(speed);
}
int BallController::ballangle(int i){
	float v1x,v1y,v2x,v2y;
	float inner=0;
	float val=0;
	if(i>=1 && i<LOOP){
		v2x = (float)((point[i].x-point[(i-1)].x)/second);		//���xv2�̂�����
		v2y = (float)((point[i].y-point[(i-1)].y)/second);		//���xv2�̂�����
		v1x = (float)((point[(i+1)].x-point[i].x)/second);		//���xv1�̂�����
		v1y = (float)((point[(i+1)].y-point[i].y)/second);		//���xv1�̂�����
		//cout<<"i="<<i<<endl;
		inner = v1x*v2x+v1y*v2y;
		//val = angle_Bound*ballspeed(i)*ballspeed(i+1);
		val = angleBound*sqrt(v2x*v2x+v2y*v2y)*sqrt(v1x*v1x+v1y*v1y);
	}else{
		//cout<<i<<endl;
		//cout<<"exception! BallAngle" << endl;
		//exit(0);
	}
	if(inner >= val){
		return(1);
	}else{
		return(0);
	}
}
float BallController::playerspeed(int loop, int index){
	float speed=0,vx,vy;
	if(loop >= 1){
		vx = (float)((point_p[index+loop*NUM].x-point_p[index+(loop-1)*NUM].x)/second);		//���x�̂�����
		vy = (float)((point_p[index+loop*NUM].y-point_p[index+(loop-1)*NUM].y)/second);		//���x�̂�����
		speed = sqrt(vx*vx+vy*vy);
	}else{
		//cout << "exception! PlayerSpeed" << endl;
		exit(0);
	}
	return(speed);
}
float* BallController::ballReach(CvPoint2D32f ball){
	float *time = new float[NUM];
	float dist=0;
	float ballspeed = 10*scale;	//���σ{�[�����x�͎���36�q
	
	for(int i=0;i<NUM;i++){
		/*dist = (ball.x-point[i].x)*(ball.x-point[i].x);
		dist += (ball.y-point[i].y)*(ball.y-point[i].y);
		dist = sqrt(dist);
		time[i] = dist/ballspeed;
		if(time[i] > MAXR){
			time[i] = MAXR;
		}
		if(time[i] < MAXR/4){
			time[i] = MAXR/4;
		}*/
		time[i] = MAXR;
	}

	return(time);
}
//�{�[���̏�ԁishot,keep,mix_up,others�j��Ԃ��B
ConstNum::Condition BallController::ballcondition(int moment){
	initneighbor();
	neighbor(moment);
	if((ballangle(moment)==1) && ballspeed(moment)>=shotBound){
	//if(ballspeed(moment)>=shot_Bound){
		//cout<<"shot"<<endl;
		return(ConstNum::shot);
	}else if(n_set.size()==1){
		//cout<<"keep"<<endl;
		return(ConstNum::keep);
	}else if(n_set.size() > 1){
		//cout<<"mix_up"<<endl;
		return(ConstNum::mix_up);
	}else{
		//cout<<"others"<<endl;
		return(ConstNum::others);
	}
}
//�{�[���̑����iteamA,teamB,team()�j��Ԃ��B
ConstNum::Attribution BallController::ballattribution(int moment){
	int index=0;
	int cond = ballcondition(moment);
	if(cond==0){
		//cout << "Ball condition is pass." << endl;
		if(moment==1){
			//cout << "exception!! BallAngle" << endl;
			return(ConstNum::own_b);
		}else{
			return(ballattribution(moment-1));
		}
	}else{
		//cout << " Number of player in the neighbor of ball is "<< n_set.size() << endl;
		stack<int> st1,st2;
		//cout<<" Index of player in the neighbor of ball is ";
		while(!n_set.empty()){
			index = n_set.top();
			n_set.pop();
			//cout<<index<<",";
			if((1 <= index)&&(index <= NUM/2)){
				st1.push(index);
			}else{
				st2.push(index);
			}
		}
		//cout<<endl;
		if(st1.empty() || st2.empty()){
			if(st1.empty() && st2.empty()){
				//cout<<"own_w"<<endl;
				return(ConstNum::own_w);
			}else if(st1.empty()){
				//cout<<"own_b"<<endl;
				return(ConstNum::own_b);
			}else{
				//cout<<"own_a"<<endl;
				return(ConstNum::own_a);
			}
		}else{
			//cout<<"own_w"<<endl;
			return(ConstNum::own_w);
		}
		delete &st2;
		delete &st1;
	}
}
