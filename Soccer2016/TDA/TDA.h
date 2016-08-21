#ifdef TDA_EXPORTS
#define TDA_API __declspec(dllexport) 
#else
#define TDA_API __declspec(dllimport) 
#endif
#pragma once
#include "stdafx.h"
using namespace std;

class TDA{
private:
	int radius;
	vector<CvPoint2D32f> k_0;
	vector<pair< CvPoint2D32f, CvPoint2D32f>> k_1;
	vector<tuple< CvPoint2D32f, CvPoint2D32f, CvPoint2D32f>> k_2;

	void CreatePair();
	void CreateTuple();
public:
	TDA_API TDA(int r, int NUM, CvPoint2D32f *point);
	TDA_API TDA(int r, vector<CvPoint2D32f> players);
	TDA_API TDA();
	TDA_API ~TDA();
	TDA_API vector<pair< CvPoint2D32f, CvPoint2D32f>> getPairs();
	TDA_API vector<tuple< CvPoint2D32f, CvPoint2D32f, CvPoint2D32f>> getTuples();
};