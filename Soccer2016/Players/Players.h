#ifdef PLAYERS_EXPORTS
#define PLAYERS_API __declspec(dllexport) 
#else
#define PLAYERS_API __declspec(dllimport) 
#endif
#pragma once
#include "stdafx.h"

class Players{
private:
	int NUM;
	int* order;
	float* value;
	float *x;
	float *y;
	ConstNum *cn;
	int LOOP;
	float* angle;
	float *velocity;
	ConstNum::PlayerType *type;
	float speedOfPoint(int t);
	float angleOfBall(int t);
public:
	PLAYERS_API Players();
	PLAYERS_API Players(float *ix, float *iy, ConstNum *constNum);

	PLAYERS_API int* getOrder();
	
	PLAYERS_API void setOrder(int* ord);

	PLAYERS_API float* getValue();

	PLAYERS_API void setValue(int x, int y, int i, float v);

	PLAYERS_API void setValue(float *v);

	PLAYERS_API float* getX();

	PLAYERS_API float* getY();

	PLAYERS_API void setX(float* input_x);

	PLAYERS_API void setY(float* input_y);

	PLAYERS_API float* getVerocity();

	PLAYERS_API void setVerocity(float* vel);

	PLAYERS_API int getLLD(int num, int t);

	PLAYERS_API stack<int> getLD(int num, int t);

	~Players(void);
};