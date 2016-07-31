// Line.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//
#include "stdafx.h"
#include "Line.h"

bool compX(const CvPoint2D32f& left, const CvPoint2D32f& right){
	return(left.x < right.x);
}

bool compRX(const CvPoint2D32f& left, const CvPoint2D32f& right){
	return(left.x > right.x);
}

bool compY(const CvPoint2D32f& left, const CvPoint2D32f& right){
	return(left.y < right.y);
}

Line::Line(vector<CvPoint2D32f> p, bool rev){
	delta = 10;
	players = p;
	if(rev){
		sort( players.begin(), players.end(), compX);
	}else{
		sort( players.begin(), players.end(), compRX);
	}
}

Line::Line(){
	delta = 10;
}

Line::~Line(){
}

int Line::getOrder(CvPoint2D32f player){
	int order = 0;
	return(order);
}

float Line::inner(vector<float> x, vector<float> y){
	float result = 0;
	size_t size = x.size();
	for(size_t i=0; i<size;i++){
		result += x.at(i)*y.at(i);
	}
	return(result);
}

float Line::norm(vector<float> x){
	return(inner(x,x));
}

float Line::mean(vector<float> x){
	float result = 0;
	size_t size = x.size();
	for(size_t i=0; i<size;i++){
		result += x.at(i);
	}
	result /= size;
	return(result);
}

float Line::deviation(vector<float> x){
	float mean = Line::mean(x);
	float result = 0;
	size_t size = x.size();
	for(size_t i=0; i<size;i++){
		result += (x.at(i)-mean)*(x.at(i)-mean);
	}
	return(result);
}

float Line::deviationXY(vector<float> x, vector<float> y){
	float meanX = Line::mean(x);
	float meanY = Line::mean(y);
	float result = 0;
	size_t size = x.size();
	for(size_t i=0; i<size;i++){
		result += (x.at(i)-meanX)*(y.at(i)-meanY);
	}
	return(result);
}

vector<CvPoint2D32f> Line::getDLastLine(){
	sort(d1Line.begin(), d1Line.end(), compY);
	return(d1Line);
}

vector<CvPoint2D32f> Line::getDLine(){
	sort(d2Line.begin(), d2Line.end(), compY);
	return(d2Line);
}

vector<float> Line::calcMat(int num){
	vector<float> vec;
	vector<float> vec_x,vec_y;
	float m11=0,m12=0,m21=0,m22=0;
	float ramda=0,u=0;
	vector<CvPoint2D32f> line = (num==0)? d1Line: d2Line;
	int INF = 1000000;

	for(size_t i=0;i<line.size();i++){
		vec_x.push_back(line.at(i).x);
		vec_y.push_back(line.at(i).y);
	}
	m11 = deviation(vec_x);
	m12 = deviationXY(vec_x, vec_y);
	m21 = deviationXY(vec_x, vec_y);
	m22 = deviation(vec_y);
	//cout<<"M11="<<m11<<", M12="<<m12<<", M21="<<m21<<", M22="<<m22<<endl;
	ramda = min(((m11+m22)-sqrt((m11+m22)*(m11+m22)-4*(m11*m22+m12*m21)))/2,
				((m11+m22)+sqrt((m11+m22)*(m11+m22)-4*(m11*m22+m12*m21)))/2);
	u = (ramda-m22)/m21;
	vec.push_back(u/sqrt(1+u*u));
	vec.push_back(1/sqrt(1+u*u));
	vec.push_back(-vec.at(0)*mean(vec_x)-vec.at(1)*mean(vec_y));
	if((m11+m22)*(m11+m22)-4*(m11*m22+m12*m21)<0){
		vec.at(0) = (float)INF;vec.at(1) = (float)INF;vec.at(2) = (float)INF;
	}
	//cout<<"ramda="<<ramda<<", A="<<vec.at(0)<<", B="<<vec.at(1)<<", C="<<vec.at(2)<<endl;
	return(vec);
}

float Line::calcError(int num, vector<float> abc){
	float err=0;
	vector<CvPoint2D32f> line = (num==0)? d1Line: d2Line;
	size_t size = line.size();

	for(size_t i=0;i<size;i++){
		CvPoint2D32f p = line.at(i);
		float e = abc.at(0)*p.x+abc.at(1)*p.y+abc.at(2);
		err += e*e;
	}
	err /= size*size;
	//cout<<"誤差:"<<err<<endl;
	return(err);
}

void Line::calcDLine(){
	int init = 3;
	int counter = init;
	vector<float> abc;
	bool flag = true;
	float err=0,p_err=1;
	
	for(int i=0;i<counter;i++) 	d1Line.push_back(players.at(i));
	abc = calcMat(0);
	p_err = calcError(0, abc);
	if(p_err > 10000){
		p_err=0;
		d1Line.pop_back();
		flag = false;
	}
	while(flag){
		d1Line.push_back(players.at(counter++));
		abc = calcMat(0);
		err = calcError(0, abc);
		//cout<<"Error :"<<p_err<<", "<<err<<endl;
		if((err > p_err+delta)||(counter >= players.size())){
			d1Line.pop_back();
			flag = false;
		}
		p_err = err;
	}

	flag = true;
	err=0,p_err=1;
	counter = (int)d1Line.size();
	for(int i=counter;(i<counter+init)&&(i<players.size());i++) 
		d2Line.push_back(players.at(i));
	abc = calcMat(1);
	p_err = calcError(1, abc);
	//cout<<"Error :"<<p_err<<", "<<endl;
	if(p_err > 10000){
		p_err=0;
		d2Line.pop_back();
		flag = false;
	}
	while(flag){
		d2Line.push_back(players.at(counter++));
		abc = calcMat(1);
		err = calcError(1, abc);
		if(err > p_err+delta){
			d2Line.pop_back();
			flag = false;
		}
		if(counter >= players.size()) flag = false;
		p_err = err;
	}
}