#ifdef BALLCONTROLLER_EXPORTS
#define BALLCONTROLLER_API __declspec(dllexport) 
#else
#define BALLCONTROLLER_API __declspec(dllimport) 
#endif
#pragma once
#include "stdafx.h"

using namespace std;
using namespace cv;

class BallController
{
private:
	CvPoint2D32f *point;
	CvPoint2D32f *point_p;
	float shotBound;
	float angleBound;
	int LOOP;
	int NUM;
	int EP;
	float second;
	stack<int> n_set;
	//�ߖT�ɂ���I��̏W���̏�����
	void initneighbor();
	//�{�[���̋ߖT�ɂ���I���index��ۑ�
	void neighbor(int moment);
	//�u��i�ɂ�����{�[���̑����Ԃ��B
	float ballspeed(int i);
	int ballangle(int i);
	float playerspeed(int i, int index);
public:
	BALLCONTROLLER_API BallController(Ball *ball,Players *players, ConstNum *cn);
	BALLCONTROLLER_API BallController();
	BALLCONTROLLER_API ~BallController();
	//�{�[���̏�ԁishot,keep,mix_up,others�j��Ԃ��B
	BALLCONTROLLER_API ConstNum::Condition ballcondition(int moment);
	//�{�[���̑����iteamA,teamB,team()�j��Ԃ��B
	BALLCONTROLLER_API ConstNum::Attribution ballattribution(int moment);
};

