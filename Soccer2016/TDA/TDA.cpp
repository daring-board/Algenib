// TDA.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//
#include "stdafx.h"
#include "TDA.h"

TDA::TDA(int r, int NUM, CvPoint2D32f *point){
	radius = r;
	for(int i=1;i<NUM/2;i++){
		if(NUM/2 != i) k_0.push_back(point[i]);
	}
	CreatePair();
	CreateTuple();
}

TDA::TDA(){
}

TDA::~TDA(){
}

void TDA::CreatePair(){
	float a, b, c, d;
	float tmp1, tmp2;
	float dist = 0;
	CvPoint2D32f pi, pj;
	for(int i=0;i<k_0.size(); i++){
		for(int j=i+1;j<k_0.size();j++){
			pi = k_0.at(i);
			pj = k_0.at(j);
			a = pi.x + pj.x;
			b = pi.x - pj.x;
			c = pi.y + pj.y;
			d = pi.y - pj.y;
			tmp1 = (a*b+c*d)/2;
			tmp2 = sqrtf(b*b+d*d);
			dist = abs(b*pi.x+d*pi.y-tmp1)/tmp2;
			//cout<<dist<<", "<< tmp2<<endl;
			if(dist < radius){
				//cout<<"("<<pi.x<<","<<pi.y<<") ("<<pj.x<<","<<pj.y<< ")"<<endl;
				k_1.push_back(pair<CvPoint2D32f, CvPoint2D32f>(pi,pj));
			}
		}
	}

}
void TDA::CreateTuple(){
	float a, b, c;
	float s, r;
	CvPoint2D32f pi, pj, pk;
	for(int n=0;n<k_1.size();n++){
		pi = k_1.at(n).first;
		pj = k_1.at(n).second;
		for(int m=0;m<k_0.size();m++){
			pk = k_0.at(m);
			a = sqrt((pi.x-pj.x)*(pi.x-pj.x)+(pi.y-pj.y)*(pi.y-pj.y));
			b = sqrt((pj.x-pk.x)*(pj.x-pk.x)+(pj.y-pk.y)*(pj.y-pk.y));
			c = sqrt((pk.x-pi.x)*(pk.x-pi.x)+(pk.y-pi.y)*(pk.y-pi.y));
			s = (a+b+c)/2;
			r = (a*b*c)/(4*sqrt(s*(s-a)*(s-b)*(s-c)));
			//cout<<r<<", "<<(4*sqrt(s*(s-a)*(s-b)*(s-c)))<<endl;
			if(r < radius){
				//cout<<" under "<<(4*sqrt(s*(s-a)*(s-b)*(s-c)))<<endl;
				//cout<<"("<<pi.x<<","<<pi.y<<") ("<<pj.x<<","<<pj.y<<") ("<<pk.x<<","<<pk.y<<")"<<endl;
				k_2.push_back(make_tuple(pi,pj,pk));
			}
		}
	}

}

vector<pair< CvPoint2D32f, CvPoint2D32f>> TDA::getPairs(){
	return(k_1);
}

vector<tuple< CvPoint2D32f, CvPoint2D32f, CvPoint2D32f>> TDA::getTuples(){
	return(k_2);
}

