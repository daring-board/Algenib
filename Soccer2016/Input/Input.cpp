#include "stdafx.h"
#include "Input.h"
	
vector<string> Input::split(const string &str, const string &delim){
	vector<string> res;
	size_t current = 0, found, delimlen = delim.size();
	while((found = str.find(delim, current)) != string::npos){
		res.push_back(string(str, current, found - current));
		current = found + delimlen;
	}
	res.push_back(string(str, current, str.size() - current));
	return res;
}
void Input::installBall(float *x, float *y){
	ball = new Ball(x,y,cn);
}
void Input::installPlayers(float *px, float *py){
	playersList = new Players(px,py,cn);
}

Input::Input(string iniPath, string dataPath){
	cn = new ConstNum(iniPath);
	cn->initData();
	map<string, string>::iterator iter = cn->properyMap.begin();
	/*while(iter != cn->properyMap.end()){
		cout << iter->first << "= " << iter->second << endl;
		iter++;
	}*/
	LOOP = cn->getLoop();
	NUM = cn->getPointNUM();
	cout<<LOOP<<","<<NUM<<endl;

	int flag=0;
	const char* str = dataPath.c_str();
	//ファイルオープン
	while(flag==0){
		fopen_s(&fp,str,"r");	
		if(fp == NULL){
			cout << "File open error!! Such file Not exist.\n" << endl;
		}else{
			flag=1;
		}
	}	
}
Input::Input(){
	cn = new ConstNum("soccer.ini");
	cn->initData();
	map<string, string>::iterator iter = cn->properyMap.begin();
	/*while(iter != cn->properyMap.end()){
		cout << iter->first << "= " << iter->second << endl;
		iter++;
	}*/
	LOOP = cn->getLoop();
	NUM = cn->getPointNUM();
	cout<<LOOP<<","<<NUM<<endl;

	int flag=0;
	char* str = "first.txt";
	//ファイルオープン
	while(flag==0){
		fopen_s(&fp,str,"r");	
		if(fp == NULL){
			cout << "File open error!! Such file Not exist.\n" << endl;
		}else{
			flag=1;
		}
	}	
}
Input::~Input(){
	delete cn;
	fclose(fp);
}	

void Input::installCoodinate(){
	vector<string> strList;
	istringstream is;
	float tmp_x,tmp_y;
	int loop = 0;

	float *x = new float[LOOP];
	float *y = new float[LOOP];
	float *px = new float[LOOP*(NUM-1)];
	float *py = new float[LOOP*(NUM-1)];

	scale = cn->getScale();
	space = cn->getSpace();

	while ( (loop <= LOOP) ) {
		int i;
		//cout << loop << endl;
		for (i = 0; i < NUM; i++) {
			if( fscanf_s(fp, "%f%f", &tmp_x, &tmp_y) != 2) {
				printf("Can not convert text to 2 floats in point[%d][%d]\n", loop, i);
				break;
			}
			if(i==0){
				x[loop] = tmp_x*scale + space;
				y[loop] = tmp_y*scale + space;
			}else{
				px[(i-1)+loop*(NUM-1)] = tmp_x*scale + space;
				py[(i-1)+loop*(NUM-1)] = tmp_y*scale + space;
			}
		}

		if(i == NUM) { // not break 1行分のデータ全部読めた
			loop++;
		}else{       // break 
						// 何かする?
			exit(1);
		}
	}

	installBall(x,y);
	installPlayers(px,py);
}
	
Ball* Input::getBall(){
	return(ball);
}

Players* Input::getPlayersList(){
	return(playersList);
}

ConstNum* Input::getConstNum(){
	return(cn);
}
