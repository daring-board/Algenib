// SPAD.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//
#include "stdafx.h"
#include "SPAD.h"
int SPAD_INF = 9999;

//Constractor
SPAD::SPAD(Subdiv2D div, int num){
	cout<<"Constract SPAD Object"<<endl;
	cout<<num<<endl;
	size = num;
	subdiv = div;
	vector<Vec4f> edgeList;
	// 辺のリストを取得
	subdiv.getEdgeList(edgeList);
	Point2f p( 0, 0);
	createIdxMap();

	// 隣接性の取得
	Node node1(p, 0);
	Node node2(p, 0);
	//int node1, node2;
	bool flag = true;
	float x=0,y=0;
	for(auto edge = edgeList.begin(); edge != edgeList.end(); edge++)
	{
		Point2f p1(edge->val[0], edge->val[1]);
		Point2f p2(edge->val[2], edge->val[3]);
		if( !(abs(edge->val[0]) == 2820 || abs(edge->val[1]) == 2820
			|| abs(edge->val[2]) == 2820 || abs(edge->val[3]) == 2820) ){
				node1 = addNode(p1);
				node2 = addNode(p2);
				x = p1.x - p2.x;
				y = p1.y - p2.y;
				x = x * x;
				y = y * y;
				addChild(node1.id, node2, sqrt(x+y));
				addChild(node2.id, node1, sqrt(x+y));
		}
	}
	showAdjList();
}

float SPAD::calcShortestPath(int start, int end){
	return dijkstra(start, end);
}

float SPAD::dijkstra(int start, int end){
	return 0;
}

void SPAD::createIdxMap(){
	idxList = new Point2f[size];
	for(int idx=0; idx < size; idx++) idxList[idx] = subdiv.getVertex(idx+4);
}

SPAD::Node SPAD::addNode(Point2f p){
	int idx = 0;
	Node n(p, 0);
	for(idx=0; idx < size; idx++){
		if(idxList[idx].x == p.x && idxList[idx].y == p.y) break;
	}
	n.id = idx;
	bool flag = true;
	for(int i=0;i<graph.size();i++){
		if(graph.at(i).id == idx) flag = false;
	}
	if(flag) graph.push_back(n);
	return n;
}

void SPAD::addChild(int pIdx, Node child, float dist){
	int idx = 0;
	for(int i=0;i<graph.size();i++){
		if(graph.at(i).id == pIdx){
			idx = i;
			break;
		}
	}
	graph.at(idx).children.push_back(child);
	graph.at(idx).wList.push_back(dist);
}

void SPAD::showAdjList(){
	Node node(Point2f( 0, 0), 0);
	for(int i=0;i<graph.size();i++){
		cout<<i<<": ";
		node = graph.at(i);
		for(int j=0;j<node.children.size();j++){
			cout<<node.children.at(j).id<<", ";
		}
		cout<<endl;
	}
}
