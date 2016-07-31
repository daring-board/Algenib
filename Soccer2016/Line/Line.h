#ifdef LINE_EXPORTS
#define LINE_API __declspec(dllexport) 
#else
#define LINE_API __declspec(dllimport) 
#endif

#include "stdafx.h"
using namespace cv;
using namespace std;

class Line{
private:
	float delta;
	vector<CvPoint2D32f> players;
	int *order;
	vector<CvPoint2D32f> d1Line;
	vector<CvPoint2D32f> d2Line;
	int getOrder(CvPoint2D32f p);
	float inner(vector<float> x, vector<float> y);
	float norm(vector<float> x);
	float mean(vector<float> x);
	float deviation(vector<float> x);
	float deviationXY(vector<float> x, vector<float> y);
	vector<float> calcMat(int num);
	float calcError(int num, vector<float> abc);
public:
	LINE_API Line(vector<CvPoint2D32f> p, bool r);
	LINE_API Line();
	LINE_API  ~Line();
	LINE_API void calcDLine();
	LINE_API vector<CvPoint2D32f> getDLastLine();
	LINE_API vector<CvPoint2D32f> getDLine();
};