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
	Point2f *nodes;
	map<int, vector<int>> eList;
	map<int, vector<float>> wList;
	vector<int> path;
	Point2f *idxList;
	Subdiv2D div;

	int addNode(Point2f p);
	void showAdjList();
	float getMinEdge(int n, int node, float **opt);
	void showPath(float **opt, int start, int end);
	void createIdxMap();
	void dikstra(int start, int end);
	void bellmanFord(int start, int end);

public:
	SPA_API SPA(Subdiv2D subdiv, int n);
	void SPA_API drawGraph(Mat img);
	void SPA_API calcShotestPath(int start, int end, int option=0);
};