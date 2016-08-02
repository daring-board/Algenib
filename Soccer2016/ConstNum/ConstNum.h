#ifdef CONSTNUM_EXPORTS
#define CONSTNUM_API __declspec(dllexport) 
#else
#define CONSTNUM_API __declspec(dllimport) 
#endif
#pragma once
#include "stdafx.h"
using namespace std;

class ConstNum{
private:
	string filePath;
public:
	CONSTNUM_API static enum Condition{
		shot, keep, mix_up, others
	};

	CONSTNUM_API static enum Attribution{
		own_a, own_b, own_w
	};

	CONSTNUM_API static enum Right{
		off_a, off_b
	};

	CONSTNUM_API static enum ConditionOfGame{
		suspend, progress
	};

	map<string, string> properyMap;

	CONSTNUM_API ConstNum();
	CONSTNUM_API ConstNum(string input_filePath);
	CONSTNUM_API ~ConstNum();
	
	CONSTNUM_API void initData();
	CONSTNUM_API int getFieldWidth();
	CONSTNUM_API int getFieldHeight();
	CONSTNUM_API float getGoal();
	CONSTNUM_API int getScale();
	CONSTNUM_API int getSpace();
	CONSTNUM_API int getLoop();
	CONSTNUM_API float getSecond();
	CONSTNUM_API int  getPointNUM();
	CONSTNUM_API float getShotBound();
	CONSTNUM_API float getAngleBound();
	CONSTNUM_API float getRadius();
	CONSTNUM_API int getBallStop();
	CONSTNUM_API float getEpsilon();
	CONSTNUM_API float getDelta();
	CONSTNUM_API float getDist();
	CONSTNUM_API int getINF();
	CONSTNUM_API int getREPET();
	CONSTNUM_API int getBiREPET();
	CONSTNUM_API float getEPSILON();
	CONSTNUM_API float getVMax();
	CONSTNUM_API float getResist();
	CONSTNUM_API float getError();
};