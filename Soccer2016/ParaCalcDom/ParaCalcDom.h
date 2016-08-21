#ifdef PARACALCDOM_EXPORTS
#define PARACALCDOM_API __declspec(dllexport) 
#else
#define PARACALCDOM_API __declspec(dllimport) 
#endif
#pragma once
#include "stdafx.h"
#define inita 0
#define initb 3
#define GAM 0.5	//î≠äˆÇ≈Ç´ÇÈâ¡ë¨ìxÇÃç≈í·

using namespace std;
using namespace cv;
using namespace tbb;

class ParaCalcDom{
	Mat img;
	ConstNum *cn;
	Players *playersList;
	CvPoint2D32f *bb_mini;
	CvPoint2D32f *bb_maxi;
	int NUM;
	int LOOP;
	int scale;
	int hspace;
	int wspace;
	float second;
	float EPS;
	int INFI;
	int RE;
	int bRE;
	int moment;
	int VMax;
	int RESIST;
	float *reachTime;
	
public:

	PARACALCDOM_API ParaCalcDom(Mat image, Players *pL, ConstNum *constNum, int time);

	PARACALCDOM_API void setBallReach(float *time);

	PARACALCDOM_API void operator() (const blocked_range<int>& range) const;

	PARACALCDOM_API void dominantrect(int offense);

	PARACALCDOM_API CvPoint2D32f* getBoundingBoxMin();
	PARACALCDOM_API CvPoint2D32f* getBoundingBoxMax();

};