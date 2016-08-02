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
	//近傍にいる選手の集合の初期化
	void initneighbor();
	//ボールの近傍にいる選手のindexを保存
	void neighbor(int moment);
	//瞬間iにおけるボールの速さ返す。
	float ballspeed(int i);
	int ballangle(int i);
	float playerspeed(int i, int index);
public:
	BALLCONTROLLER_API BallController(Ball *ball,Players *players, ConstNum *cn);
	BALLCONTROLLER_API BallController();
	BALLCONTROLLER_API ~BallController();
	//ボールの状態（shot,keep,mix_up,others）を返す。
	BALLCONTROLLER_API ConstNum::Condition ballcondition(int moment);
	//ボールの属性（teamA,teamB,team()）を返す。
	BALLCONTROLLER_API ConstNum::Attribution ballattribution(int moment);
};

