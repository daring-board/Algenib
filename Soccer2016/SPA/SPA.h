#ifdef SPA_EXPORTS
#define SPA_API __declspec(dllexport) 
#else
#define SPA_API __declspec(dllimport) 
#endif
#pragma once
#include "stdafx.h"
using namespace std;
using namespace cv;

class SPA{
private:
	int num;
	Point *nodes;
	map<int, vector<int>> eList;
	map<int, vector<float>> wList;
	int addNode(Point p);
	void showAdjList();

public:
	SPA_API SPA(Subdiv2D subdiv, int n);
	void SPA_API drawGraph(Mat img);
	void SPA_API calcShotestPath(int start, int end);
};