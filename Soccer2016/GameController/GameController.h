#ifdef GAMECONTROLLER_EXPORTS
#define GAMECONTROLLER_API __declspec(dllexport) 
#else
#define GAMECONTROLLER_API __declspec(dllimport) 
#endif
#pragma once
#include "stdafx.h"
using namespace cv;

class GameController{
private:
	Ball *ball;
	BallController *bc;
	int LOOP;
	int wspace;
	int hspace;
	int FIELD_width;
	int FIELD_height;
	int scale;
	float goal;
	int BALLstop;
	float DELT;

	ConstNum::ConditionOfGame sus_or(int moment);

	ConstNum::ConditionOfGame pro_or(int moment);

	int in_goalaria(CvPoint2D32f b);

	int in_field(CvPoint2D32f b);

	int on_FK(CvPoint2D32f b,int moment);

	int stillness(CvPoint2D32f b,int moment);

	int excepteness(int moment);

	ConstNum::Right isOff(int l,int m);

public:
	GAMECONTROLLER_API GameController(Ball *b, BallController *ballCon, ConstNum *cn);

	GAMECONTROLLER_API ConstNum::ConditionOfGame getCondition(ConstNum::ConditionOfGame condition,int k);

	GAMECONTROLLER_API ConstNum::Right getOff(int loop);

};