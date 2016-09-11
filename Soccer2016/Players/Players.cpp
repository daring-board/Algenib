#include "stdafx.h"
#include "Players.h"

	float Players::speedOfPoint(int t){
		float speed = 0;
		float sx,sy;
		float second;

		map<string, string>::iterator iter = cn->properyMap.begin();
		iter = cn->properyMap.find("second ");
		istringstream SECOND((*iter).second);
		SECOND >> second;

		sx = x[t]-x[t-1];
		sy = y[t]-y[t-1];
		sx *= sx;
		sy *= sy;
		speed = (float)(sqrt((sx+sy)/second));
		return(speed);
	}
	float Players::angleOfBall(int t){
		float angle = 0;
		float second;

		map<string, string>::iterator iter = cn->properyMap.begin();
		iter = cn->properyMap.find("loop ");
		istringstream SECOND((*iter).second);
		SECOND >> second;

		if(t!=0){
			float v1x,v1y,v2x,v2y,sx,sy;
			v1x = (float) ((x[t]-x[t-1])/second);
			v1y = (float) ((y[t]-y[t-1])/second);
			v2x = (float) ((x[t+1]-x[t])/second);
			v2y = (float) ((y[t+1]-y[t])/second);
			sx = (float) sqrt(v1x*v1x+v1y*v1y);
			sy = (float) sqrt(v2x*v2x+v2y*v2y);
			angle = (float)((v1x*v2x+v1y*v2y)/(sx*sy));
		}else{
			angle = 0;
		}
		
		return angle;
	}


	Players::Players(){};
	Players::Players(float *ix, float *iy, ConstNum *constNum){
		cn = constNum;
		LOOP = cn->getLoop();
		NUM = cn->getPointNUM()-1;
		angle = new float[LOOP];

		x = ix;
		y = iy;
		velocity = new float[LOOP];
		int width = cn->getFieldWidth()*cn->getScale()+2*cn->getSpace();
		int height = cn->getFieldHeight()*cn->getScale()+2*cn->getSpace();
		order = new int[NUM*LOOP];
		type = new ConstNum::PlayerType[NUM*LOOP];
		value = new float[width*height*NUM];
		memset(value, constNum->getINF(), width*height*NUM);
	}

	Players::~Players(void)
	{
		delete angle;
		delete velocity;
		delete order;
		delete value;
	}

	int* Players::getOrder() {
		return order;
	}
	
	void Players::setOrder(int* ord) {
		order = ord;
	}

	float* Players::getValue(){
		return(value);
	}

	void Players::setValue(int x, int y, int i, float v){
		int height = cn->getFieldHeight()*cn->getScale()+2*cn->getSpace();
		value[i+(y+x*height)*NUM] = v;
	}

	void Players::setValue(float *v){
		value = v;
	}

	float* Players::getX(){
		return(x);
	}

	float* Players::getY(){
		return(y);
	}

	void Players::setX(float* input_x){
		x = input_x;
	}

	void Players::setY(float* input_y){
		y = input_y;
	}

	float* Players::getVerocity(){
		return(velocity);
	}

	void Players::setVerocity(float* vel){
		velocity = vel;
	}

	int Players::getLLD(int time, int t){
		bool flag = false;
		int index = 1;
		float tmp = (t == 0)? 1000: 0;
		int start, end;
		if(t == 0){
			start = 1;
			end = NUM/2;
		}else{
			start = NUM/2+1;
			end = NUM;
		}
		for(int j=start;j<end;j++){
			if(j == NUM/2) continue;
			flag = false;
			flag = (t==0)? (x[j+time*NUM] < tmp): (x[j+time*NUM] > tmp);
			if(flag){
				tmp = x[j+time*NUM];
				index = j;
			}
		}
		type[index+time*NUM] = ConstNum::PlayerType::LLD;
		return(index);
	}

	stack<int> Players::getLD(int time, int t){
		bool flag = false;
		int index = 0;
		stack<int> st;
		int start, end;
		if(t == 0){
			start = 1;
			end = NUM/2;
		}else{
			start = NUM/2+1;
			end = NUM;
		}
		for(int j=start;j<end;j++){
			if(type[j+time*NUM] == ConstNum::PlayerType::LLD){
				index = j;
				break;
			}
		}
		for(int j=start;j<end;j++){
			if((x[index+time*NUM] <= x[j+time*NUM])
				&& (x[index+time*NUM]+2 > x[j+time*NUM])){
					type[j+time*NUM] = ConstNum::PlayerType::LD;
					st.push(j);
			}
		}
		return(st);
	}


