#ifdef VIEW_EXPORTS
#define VIEW_API __declspec(dllexport) 
#else
#define VIEW_API __declspec(dllimport) 
#endif
#pragma once
#include "stdafx.h"
using namespace cv;

class View
{
public :
	typedef struct{
		int start;
		int end;
	}Interval;
private:
	Mat img;
	ConstNum *cn;
	char *str;
	Ball *ball;
	Players *playersList;
	int NUM;
	int LOOP;
	int ballSize;
	int playerSize;
	enum type{ TF=0, TS=1, TA=2};
	Interval getTeam(int flag);
public:
	VIEW_API View(void);
	VIEW_API View(Input *ip, char *name);
	VIEW_API ~View(void);
	void refresh(void);
	void drawfield(void);
	VIEW_API void show(BallController bc, int t);
	void drawBall(int t);
	void drawPlayers(int t);
	void drawDelaunay(Subdiv2D subdiv, type t);
	Subdiv2D divideSurface(int time, type t);
	Line calcLine(int time, type t);
	void drawLine(Line dline, type t);
	TDA calcTDA(int time, type t);
	void drawTDAPair(TDA tda, type t);
	void drawTDATriangle(TDA tda, type t);
	void calcurateDominant(int time, BallController bc);
	void drawDominant(int time, BallController bc, type t);
	void drawOffsideLine(int time, type t);
	void divideField(int time, type t);
};

