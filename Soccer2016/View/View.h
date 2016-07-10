#ifdef VIEW_EXPORTS
#define VIEW_API __declspec(dllexport) 
#else
#define VIEW_API __declspec(dllimport) 
#endif

class View
{
private:
	IplImage *img;
	ConstNum *cn;
public:
	View(void);
	View(Input *ip);
	~View(void);
};

