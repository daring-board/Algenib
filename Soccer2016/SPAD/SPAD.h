#ifdef SPAD_EXPORTS
#define SPAD_API __declspec(dllexport) 
#else
#define SPAD_API __declspec(dllimport) 
#endif
#pragma once
#include "stdafx.h"
using namespace std;
using namespace cv;

class SPAD{
	struct Node{
		Point2f p;
		int id;
		vector<Node> children;
		vector<float> wList;
		Node(Point2f point, int idx){
			p = point;
			id = idx;
		}
	};
private:
	int size;
	vector<Node> graph;
	Subdiv2D subdiv;
	Point2f *idxList;

	Node addNode(Point2f p);
	void addChild(int pIdx, Node child, float dist);
	void showAdjList();
	void createIdxMap();
	float dijkstra(int start, int end);
public:
	SPAD_API SPAD(Subdiv2D subdiv, int n);
	SPAD_API float calcShortestPath(int start, int end);
};