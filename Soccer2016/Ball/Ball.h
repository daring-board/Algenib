#ifdef BALL_EXPORTS
#define BALL_API __declspec(dllexport) 
#else
#define BALL_API __declspec(dllimport) 
#endif

#include "stdafx.h"

class Ball{
private:
	float *x;
	float *y;
	ConstNum *cn;
	int LOOP;
	ConstNum::Condition *cond;
	ConstNum::Attribution *attr;

public:
	BALL_API Ball();
	BALL_API Ball(float* ix, float* iy, ConstNum *constNum);

	BALL_API ~Ball();
	
	BALL_API ConstNum::Condition* getCondition();
	
	BALL_API ConstNum::Attribution* getAttribution();

	BALL_API float* getX();

	BALL_API float* getY();

	BALL_API void setX(float* input_x);

	BALL_API void setY(float* input_y);
};