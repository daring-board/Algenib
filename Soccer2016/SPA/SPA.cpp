// SPA.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include "SPA.h"
int SPA_INF = 9999;

//Constractor
SPA::SPA(Subdiv2D subdiv, int size){
	cout<<"Constract SPA Object"<<endl;
	num = size;
	div = subdiv;
	vector<Vec4f> edgeList;
	// 辺のリストを取得
	subdiv.getEdgeList(edgeList);
	nodes = new Point2f[num];
	Point2f p( 0, 0);
	for(int i=0;i<num;i++) nodes[i] = p;

	// 隣接性の取得
	int index1=0, index2=0;
	bool flag = true;
	float x=0,y=0;
	for(auto edge = edgeList.begin(); edge != edgeList.end(); edge++)
	{
		Point2f p1(edge->val[0], edge->val[1]);
		Point2f p2(edge->val[2], edge->val[3]);
		if( !(abs(edge->val[0]) == 2820 || abs(edge->val[1]) == 2820
			|| abs(edge->val[2]) == 2820 || abs(edge->val[3]) == 2820) ){
				index1 = addNode(p1);
				index2 = addNode(p2);
				x = p1.x - p2.x;
				y = p1.y - p2.y;
				x = x * x;
				y = y * y;
				eList[index1].push_back(index2);
				wList[index2].push_back(sqrt(x+y));
				eList[index2].push_back(index1);
				wList[index1].push_back(sqrt(x+y));
		}
	}
	createIdxMap();
	showAdjList();
}

void SPA::createIdxMap(){
	idxList = new Point2f[num];
	for(int idx=0; idx < num; idx++) idxList[idx] = div.getVertex(idx+4);
}

// if Point2f p is not exist in nodes then push nodes vector
int SPA::addNode(Point2f p){
	Point2f init(0, 0);
	bool flag = true;
	int index = 0;
	for( index=0; index<num; index++){
		if(nodes[index] == p){
			flag = false;
			break;
		}
		if(nodes[index] == init) break;
	}
	if(flag) nodes[index] = p;
	return index;
}

void SPA::drawGraph(Mat img){
	//cout<<"drawGraph"<<endl;
	Point2f point, p;
	char* numS = new char[4];
	int font = CV_FONT_HERSHEY_SIMPLEX;

	for(int i=0;i<num;i++){
		point = nodes[i];
		int j = 0;
		for(j=0; j<num;j++){
			p = idxList[j];
			if(point.x == p.x && point.y == p.y) break; 
		}
		sprintf_s(numS, sizeof(4), "%d", j+1);
		circle(img, point, 5, Scalar( 255, 255, 255), CV_FILLED);
		putText(img, numS, point, font, 1, Scalar(255, 255, 255));
	}

	for(int i=0;i < num;i++){
		Point2f node = nodes[i];
		for(int j=0; j<eList[i].size();j++){
			line( img, nodes[i], nodes[eList[i].at(j)], Scalar( 255, 255, 255), 2, CV_AA,0);
		}
	}
}

void SPA::showAdjList(){
	//隣接リストの表示
	for(int i=0;i < num;i++){
		Point2f node = nodes[i];
		cout<<i<<": ";
		for(int j=0; j<eList[i].size();j++){
			int child = eList[i].at(j);
			cout<<"("<<eList[i].at(j)<<", "<<wList[i].at(j)<<") : ";
		}
		cout<<endl;
	}
	cout<<endl;
}

void SPA::calcShotestPath(int start, int end, int option){
		if(option == 0) bellmanFord(start, end);
		else dikstra(start, end);
}

void SPA::dikstra(int start, int end){
}

void SPA::bellmanFord(int start, int end){
	//cout<<"calcShotestPath"<<endl;
	float **M = new float*[num];
	for(int i=0; i<num; i++){
		M[i] = new float[num];
		for(int j=0; j<num; j++) M[i][j] = SPA_INF;
	}
	for(int j=0; j<num; j++){
		if(j != end-1) M[0][j] = SPA_INF;
		else M[0][end-1] = 0;
	}

	float tmp = 0;
	for(int i=1; i<num; i++){
		cout<<i<<": ";
		for(int j=0; j<num; j++){
			tmp = getMinEdge(i-1, j, M);
			M[i][j] = (M[i-1][j] < tmp)? M[i-1][j]: tmp;
			cout<< M[i][j] <<": ";
		}
		cout<<endl;
	}
	cout<<M[num-1][start]<<endl;
	showPath(M, start, end-1);
}

float SPA::getMinEdge(int i, int node, float **opt){
	//cout<<"getMinEdge"<<endl;
	float min = SPA_INF;
	float tmp = 0, weight = 0;
	int index = 0;
	for(int j=0;j<eList[node].size(); j++){
		index = eList[node].at(j);
		weight = wList[node].at(j);
		tmp = opt[i][index] + weight;
		min = (tmp < min)? tmp: min;
	}
	return min;
}

void SPA::showPath(float **opt, int start, int end){
}