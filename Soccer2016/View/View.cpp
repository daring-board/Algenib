// View.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include "View.h"
using namespace cv;

View::View(void)
{
}

View::View(Input *ip, char *name){
	str = name;
	cn = ip->getConstNum();
	//width, heightの画像を作成
	int x = cn->getFieldWidth()*cn->getScale()+2*cn->getSpace();
	int y = cn->getFieldHeight()*cn->getScale()+2*cn->getSpace();
	ball = ip->getBall();
	playersList = ip->getPlayersList();
	NUM = cn->getPointNUM();
	LOOP = cn->getLoop();
	ballSize = 5;
	playerSize = 3;
	img = Mat(y, x,  CV_8UC3);
	namedWindow (str, CV_WINDOW_AUTOSIZE);
	refresh();
}

View::~View(void)
{
}

void View::refresh(void)
{
	Point p1,p2;
	p1.x = 0;
	p1.y = 0;
	p2.x = img.cols;
	p2.y = img.rows;
	rectangle(img,p1,p2,Scalar(0, 255, 0),CV_FILLED, CV_AA);
}

void View::drawfield(void)
{
	int lineSize = 1;
	CvPoint2D32f ptf1, ptf2;  
	Point pt1,pt2;
	Scalar rcolor;
	Size parc;
	int scale = cn->getScale();
	int goal = cn->getGoal();
	int wspace = cn->getSpace();
	int hspace = cn->getSpace();

	rcolor = Scalar(255,255,255);

	//soccer field
	ptf1.x = wspace;
	ptf1.y = hspace;
	ptf2.x = (float)img.cols-wspace;
	ptf2.y = (float)img.rows-hspace;
	pt1 = cvPointFrom32f(ptf1);
	pt2 = cvPointFrom32f(ptf2);
	rectangle (img, pt1, pt2, rcolor, lineSize , CV_AA, 0);
	//draw line
		//draw center line
	ptf1.x = (float)img.cols/2;
	ptf1.y = hspace;
	ptf2.x = (float)img.cols/2;
	ptf2.y = (float)img.rows-hspace;
	pt1 = cvPointFrom32f(ptf1);
	pt2 = cvPointFrom32f(ptf2);
	line(img, pt1, pt2, rcolor, lineSize, CV_AA, 0);

		//draw center circle
	ptf1.x = (float)img.cols/2;
	ptf1.y = (float)img.rows/2;
	pt1 = cvPointFrom32f(ptf1);
	circle(img,pt1,scale*9.15,rcolor,lineSize , CV_AA, 0);
		//draw penalty area
	ptf1.x = wspace;
	ptf1.y = img.rows/2-(goal*scale/2+16.5*scale);
	ptf2.x = wspace+(16.5*scale);
	ptf2.y = (float)img.rows/2+(goal*scale/2+16.5*scale);
	pt1 = cvPointFrom32f(ptf1);
	pt2 = cvPointFrom32f(ptf2);
	rectangle (img, pt1, pt2, rcolor, lineSize , CV_AA, 0);
	ptf1.x = (float)img.cols-(wspace+(16.5*scale));
	ptf1.y = (float)img.rows/2-(goal*scale/2+16.5*scale);
	ptf2.x = (float)img.cols-wspace;
	ptf2.y = (float)img.rows/2+(goal*scale/2+16.5*scale);
	pt1 = cvPointFrom32f(ptf1);
	pt2 = cvPointFrom32f(ptf2);
	rectangle(img, pt1, pt2, rcolor, lineSize , CV_AA, 0);
		//draw goal area
	ptf1.x = wspace;
	ptf1.y = (float)img.rows/2-(goal*scale/2+5.5*scale/2);
	ptf2.x = wspace+(5.5*scale);
	ptf2.y = (float)img.rows/2+(goal*scale/2+5.5*scale/2);
	pt1 = cvPointFrom32f(ptf1);
	pt2 = cvPointFrom32f(ptf2);
	rectangle (img, pt1, pt2, rcolor,lineSize , CV_AA, 0);
	ptf1.x = (float)img.cols-(wspace+(5.5*scale));
	ptf1.y = (float)img.rows/2-(goal*scale/2+5.5*scale/2);
	ptf2.x = (float)img.cols-wspace;
	ptf2.y = (float)img.rows/2+(goal*scale/2+5.5*scale/2);
	pt1 = cvPointFrom32f(ptf1);
	pt2 = cvPointFrom32f(ptf2);
	rectangle (img, pt1, pt2, rcolor, lineSize , CV_AA, 0);
		//penalty arc
	ptf1.x = wspace+11*scale;
	ptf1.y = img.rows/2;
	parc.height = 9.15*scale;
	parc.width = 9.15*scale;
	pt1 = cvPointFrom32f(ptf1);
	ellipse(img,pt1,parc,0,-53,53,rcolor,lineSize, CV_AA, 0);
	ptf1.x = img.cols-(wspace+11*scale);
	ptf1.y = img.rows/2;
	parc.height = 9.15*scale;
	parc.width = 9.15*scale;
	pt1 = cvPointFrom32f(ptf1);
	ellipse(img,pt1,parc,0,180-53,53+180,rcolor, lineSize, CV_AA, 0);
}

void View::show(void)
{
	Subdiv2D subdiv;
	Line dl;
	for(int t=1;t<LOOP;t++){
		/*BallController bc( ball, playersList, cn);
		int ba = (int)bc.ballattribution(t);
		cout<<bc.ballcondition(t)<<ba<<endl;
		if(ba == 1){*/
			drawfield();
			subdiv = divideSurface(t, TS);
			dl = calcLine(t, TF);
			drawDelaunay(subdiv, TS);
			drawLine(dl, TF);
			drawBall(t);
			drawPlayers(t);

			imshow(str, img);
			waitKey(200);
			refresh();
		//}
	}
}

void View::drawBall(int t)
{
	Point point;
	CvPoint2D32f p_ball;

	p_ball.x = ball->getX()[t];
	p_ball.y = ball->getY()[t];
	point = cvPointFrom32f(p_ball);

	circle (img, point, ballSize, Scalar( 0, 255, 255), CV_FILLED);
}

void View::drawPlayers(int t)
{
	Point point;
	CvPoint2D32f p_player;
	int font = CV_FONT_HERSHEY_SIMPLEX;
	char* numS = new char[4];

	for(int n = 0; n < NUM-1; n++){
		p_player.x = playersList->getX()[n+t*(NUM-1)];
		p_player.y = playersList->getY()[n+t*(NUM-1)];
		point = cvPointFrom32f(p_player);
		sprintf_s(numS, sizeof(4), "%d", n);

		if(n <  (NUM-1)/2){
			circle (img, point, playerSize, Scalar(255, 0, 0), CV_FILLED);
			putText(img, numS, point, font, 0.5, Scalar(255, 0, 0));
		}else{
			circle (img, point, playerSize, Scalar(0, 0, 255), CV_FILLED);
			putText(img, numS, point, font, 0.5, Scalar(0, 0, 255));
		}
	}
	delete numS;
}

void View::drawDelaunay(Subdiv2D subdiv, type t){
	vector<Vec4f> edgeList;
	int Linesize = 1;
	Scalar color = (t==TF)? Scalar(255, 0, 0): Scalar( 0, 0, 255);
	// 辺のリストを取得
	subdiv.getEdgeList(edgeList);

	// 描画
	int i=0;
	for(auto edge = edgeList.begin(); edge != edgeList.end(); edge++)
	{
		Point p1(edge->val[0], edge->val[1]);
		Point p2(edge->val[2], edge->val[3]);
		if( !(abs(edge->val[0]) == 2820 || abs(edge->val[1]) == 2820
			|| abs(edge->val[2]) == 2820 || abs(edge->val[3]) == 2820) ){
			line( img, p1, p2, color, Linesize, CV_AA,0);
		}
	}
}

Subdiv2D View::divideSurface(int time, type t){
	int i;
	int shift;
	int pNUM = NUM-1;
	CvPoint2D32f *point = new CvPoint2D32f[pNUM];

	for(int i=0;i<pNUM;i++){
		point[i].x = playersList->getX()[i+time*pNUM];
		point[i].y = playersList->getY()[i+time*pNUM];
	}

	vector<Point2f> point_f;
	Subdiv2D subdiv;
	Interval inter = getTeam(t);
	for (i = inter.start; i < inter.end; i++) {
		if( i != pNUM/2 ){
			if(point[i].x < 0){
				point[i].x = 0;
			}
			if(point[i].x > img.cols ){
				point[i].x = img.cols-1;
			}
			if(point[i].y < 0){
				point[i].y = 0;
			}
			if(point[i].y > img.rows ){
				point[i].y = img.rows-1;
			}
			point_f.push_back(point[i]);
		}
	}
	subdiv.initDelaunay(Rect( 0, 0, img.cols, img.rows));
	subdiv.insert(point_f);

	return(subdiv);
}

View::Interval View::getTeam(int flag){
	Interval inter = {1, NUM-1};
	switch(flag){
	case (int)TF:
		inter.start = 1;
		inter.end = (NUM-1)/2;
		break;
	case (int)TS:
		inter.start = (NUM-1)/2+1;
		inter.end = NUM-1;
		break;
	case (int)TA:
		inter.start = 1;
		inter.end = NUM-1;
		break;
	}
	return inter;
}

Line View::calcLine(int time, type t)
{
	int pNUM = NUM-1;
	bool team = (t==TF)? true: false;
	CvPoint2D32f *point = new CvPoint2D32f[pNUM];
	for(int i=0;i<pNUM;i++){
		point[i].x = playersList->getX()[i+time*pNUM];
		point[i].y = playersList->getY()[i+time*pNUM];
	}
	vector<CvPoint2D32f> players;
	Interval inter = getTeam(t);
	for(int i=inter.start;i<inter.end;i++){
		players.push_back(point[i]);
	}
	Line dl(players, team);
	dl.calcDLine();
	return(dl);
}

void View::drawLine(Line dline, type t)
{
	int Linesize = 2;
	vector<CvPoint2D32f> l1,l2;
	Point p1, p2;
	Scalar color = (t==TF)? Scalar(255, 0, 0): Scalar( 0, 0, 255);
	l1 = dline.getDLastLine();
	l2 = dline.getDLine();
	for(int i=0;i<l1.size()-1;i++){
		p1 = cvPointFrom32f(l1.at(i));
		p2 = cvPointFrom32f(l1.at(i+1));
		line(img,p1,p2, color,Linesize,CV_AA,0);
	}
	for(int i=0;i<l2.size()-1;i++){
		p1 = cvPointFrom32f(l2.at(i));
		p2 = cvPointFrom32f(l2.at(i+1));
		line(img,p1,p2, color,Linesize,CV_AA,0);
	}
}
