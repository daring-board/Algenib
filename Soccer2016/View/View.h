#ifdef VIEW_EXPORTS
#define VIEW_API __declspec(dllexport) 
#else
#define VIEW_API __declspec(dllimport) 
#endif

#include "stdafx.h"
using namespace cv;

class View
{
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
public:
	VIEW_API View(void);
	VIEW_API View(Input *ip, char *name);
	VIEW_API ~View(void);
	void refresh(void);
	void drawfield(void);
	VIEW_API void show(void);
	void drawBall(int t);
	void drawPlayers(int t);
};

