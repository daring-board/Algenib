#ifdef PARAPAINTDOM_EXPORTS
#define PARAPAINTDOM_API __declspec(dllexport) 
#else
#define PARAPAINTDOM_API __declspec(dllimport) 
#endif
#pragma once
#include "stdafx.h"

using namespace cv;
using namespace tbb;
using namespace std;

class ParaPaintDom{
private:
	Mat img;
	Players *playersList;
	ConstNum *cn;
	int NUM;
	int INF;
	int width;
	int hspace;
	int wspace;
	float *reachTime;
	float dist;
	int type;
	//各選手の色を決める（HSV→RGB）
	void color(int px,int py,int agent,float time, int i) const;
public:
	PARAPAINTDOM_API ParaPaintDom(Mat image, Players *pList, ConstNum *cNum, int t);
	PARAPAINTDOM_API void setBallReach(float *time);
	//優勢領域の塗り分け
	PARAPAINTDOM_API void paint(int t);
	PARAPAINTDOM_API void operator() (const blocked_range<int>& range) const;
};