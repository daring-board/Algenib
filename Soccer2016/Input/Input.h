#ifdef INPUT_EXPORTS
#define INPUT_API __declspec(dllexport) 
#else
#define INPUT_API __declspec(dllimport) 
#endif
#pragma once
#include "stdafx.h"

using namespace std;

class Input{

private:
	FILE *fp;
	int LOOP;
	int NUM;
	ConstNum *cn;
	Ball *ball;
	Players *playersList;
	int scale;
	int space;
	
	vector<string> split(const string &str, const string &delim);
	void installBall(float *x, float *y);
	void installPlayers(float *px, float *py);
public:
	INPUT_API Input(string iniPath, string dataPath);
	INPUT_API Input();
	INPUT_API ~Input();

	INPUT_API void installCoodinate();
	
	INPUT_API Ball* getBall();

	INPUT_API Players* getPlayersList();

	INPUT_API ConstNum* getConstNum();
};