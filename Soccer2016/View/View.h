#ifdef VIEW_EXPORTS
#define VIEW_API __declspec(dllexport) 
#else
#define VIEW_API __declspec(dllimport) 
#endif

#include "stdafx.h"

class View
{
private:
	IplImage *img;
	ConstNum *cn;
	char *str;
public:
	VIEW_API View(void);
	VIEW_API View(Input *ip, char *name);
	VIEW_API ~View(void);
	void refresh(void);
	VIEW_API void drawfield(void);
	VIEW_API void show(void);
};

