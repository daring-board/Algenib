#include "stdafx.h"
#include "Ball.h"

	Ball::Ball(){};
	Ball::Ball(float* ix, float* iy, ConstNum *constNum){
		cn = constNum;
		LOOP = cn->getLoop();
		cond = new ConstNum::Condition[LOOP];
		attr = new ConstNum::Attribution[LOOP];
		for(int i=0;i<LOOP-1;i++){
			cond[i] = ConstNum::Condition::others;
			attr[i] = ConstNum::Attribution::own_w;
		}

		x = ix;
		y = iy;
	}

	Ball::~Ball(){
	}
	
	ConstNum::Condition* Ball::getCondition(){
		return(cond);
	}
	
	ConstNum::Attribution* Ball::getAttribution(){
		return(attr);
	}

	float* Ball::getX(){
		return(x);
	}

	float* Ball::getY(){
		return(y);
	}

	void Ball::setX(float* input_x){
		x = input_x;
	}

	void Ball::setY(float* input_y){
		y = input_y;
	}
