#include "stdafx.h"
#include "ConstNum.h"
#include <fstream>
#include <sstream>

using namespace std;

ConstNum::ConstNum(){}
ConstNum::ConstNum(string input_filePath){
	filePath = input_filePath;
	properyMap.clear();
}
ConstNum::~ConstNum(){}
	
void ConstNum::initData(){
	ifstream ifs(filePath);
	if(ifs.fail()){
		cout<<"Can't open file!"<<endl;
	}

	char tmp[256];
	ifs.getline(tmp, 256);
	while(!ifs.eof()){
		string line(tmp);
		// コメント行
		if(line.substr(0, 1).compare("#") != 0)
		{
			// 無効行
			size_t nEq = line.find("=");
			if(nEq != -1)
			{
				string key = line.substr(0, nEq);
				string val = line.substr(nEq+1);
				properyMap.insert(pair<string, string>(key, val));
			}
		}
		ifs.getline(tmp, 256);
	}
	ifs.close();
}
int ConstNum::getFieldWidth(){
	int f_width;
	map<string, string>::iterator iter = properyMap.begin();
	iter = properyMap.find("field_width ");
	istringstream width((*iter).second);
	width >> f_width;
	return(f_width);
}
int ConstNum::getFieldHeight(){
	int f_height;
	map<string, string>::iterator iter = properyMap.begin();
	iter = properyMap.find("field_height ");
	istringstream height((*iter).second);
	height >> f_height;
	return(f_height);
}
float ConstNum::getGoal(){
	float goal;
	map<string, string>::iterator iter = properyMap.begin();
	iter = properyMap.find("goal ");
	istringstream tmp_goal((*iter).second);
	tmp_goal >> goal;
	return(goal);
}
int ConstNum::getScale(){
	int scale;
	map<string, string>::iterator iter = properyMap.begin();
	iter = properyMap.find("scale ");
	istringstream tmp_scale((*iter).second);
	tmp_scale >> scale;
	return(scale);
}
int ConstNum::getSpace(){
	int space;
	map<string, string>::iterator iter = properyMap.begin();
	iter = properyMap.find("space ");
	istringstream tmp_space((*iter).second);
	tmp_space >> space;
	return(space);
}
int ConstNum::getLoop(){
	int loop;
	map<string, string>::iterator iter = properyMap.begin();
	iter = properyMap.find("loop ");
	istringstream tmp_loop((*iter).second);
	tmp_loop >> loop;
	return(loop);
}
float ConstNum::getSecond(){
	float second;
	map<string, string>::iterator iter = properyMap.begin();
	iter = properyMap.find("second ");
	istringstream tmp_second((*iter).second);
	tmp_second >> second;
	return(second);
}
int  ConstNum::getPointNUM(){
	int point_number;
	map<string, string>::iterator iter = properyMap.begin();
	iter = properyMap.find("point_number ");
	istringstream tmp_point_number((*iter).second);
	tmp_point_number >> point_number;
	return(point_number);
}
float ConstNum::getShotBound(){
	float shot_Bound;
	map<string, string>::iterator iter = properyMap.begin();
	iter = properyMap.find("shot_Bound ");
	istringstream tmp_shot_Bound((*iter).second);
	tmp_shot_Bound >> shot_Bound;
	return(shot_Bound);
}
float ConstNum::getAngleBound(){
	float angle_Bound;
	map<string, string>::iterator iter = properyMap.begin();
	iter = properyMap.find("angle_Bound ");
	istringstream tmp_angle_Bound((*iter).second);
	tmp_angle_Bound >> angle_Bound;
	return(angle_Bound);
}
float ConstNum::getRadius(){
	float radius;
	map<string, string>::iterator iter = properyMap.begin();
	iter = properyMap.find("radius ");
	istringstream tmp_radius((*iter).second);
	tmp_radius >> radius;
	return(radius);
}
int ConstNum::getBallStop(){
	int ball_stop;
	map<string, string>::iterator iter = properyMap.begin();
	iter = properyMap.find("ball_stop ");
	istringstream tmp_ball_stop((*iter).second);
	tmp_ball_stop >> ball_stop;
	return(ball_stop);
}
float ConstNum::getEpsilon(){
	float EPS;
	map<string, string>::iterator iter = properyMap.begin();
	iter = properyMap.find("EPS ");
	istringstream tmp_EPS((*iter).second);
	tmp_EPS >> EPS;
	return(EPS);
}
float ConstNum::getDelta(){
	float DELTA;
	map<string, string>::iterator iter = properyMap.begin();
	iter = properyMap.find("DELTA ");
	istringstream tmp_DELTA((*iter).second);
	tmp_DELTA >> DELTA;
	return(DELTA);
}
int ConstNum::getINF(){
	int INF;
	map<string, string>::iterator iter = properyMap.begin();
	iter = properyMap.find("INF ");
	istringstream tmp_INF((*iter).second);
	tmp_INF >> INF;
	return(INF);
}
float ConstNum::getEPSILON(){
	float EPSILON;
	map<string, string>::iterator iter = properyMap.begin();
	iter = properyMap.find("EPSILON ");
	istringstream tmp_EPSILON((*iter).second);
	tmp_EPSILON >> EPSILON;
	return(EPSILON);
}
int ConstNum::getREPET(){
	int RE;
	map<string, string>::iterator iter = properyMap.begin();
	iter = properyMap.find("RE ");
	istringstream tmp_RE((*iter).second);
	tmp_RE >> RE;
	return(RE);
}
int ConstNum::getBiREPET(){
	int bRE;
	map<string, string>::iterator iter = properyMap.begin();
	iter = properyMap.find("bRE ");
	istringstream tmp_bRE((*iter).second);
	tmp_bRE >> bRE;
	return(bRE);
}
float ConstNum::getDist(){
	float Dist;
	map<string, string>::iterator iter = properyMap.begin();
	iter = properyMap.find("dist ");
	istringstream tmp_Dist((*iter).second);
	tmp_Dist >> Dist;
	return(Dist);
}
float ConstNum::getVMax(){
	float VMax;
	map<string, string>::iterator iter = properyMap.begin();
	iter = properyMap.find("VMax ");
	istringstream tmp_VMax((*iter).second);
	tmp_VMax >> VMax;
	return(VMax);
}
float ConstNum::getResist(){
	float RESIST;
	map<string, string>::iterator iter = properyMap.begin();
	iter = properyMap.find("RESIST ");
	istringstream tmp_RESIST((*iter).second);
	tmp_RESIST >> RESIST;
	return(RESIST);
}
float ConstNum::getError(){
	float ERR;
	map<string, string>::iterator iter = properyMap.begin();
	iter = properyMap.find("ERROR ");
	istringstream tmp_ERROR((*iter).second);
	tmp_ERROR >> ERR;
	return(ERR);
}