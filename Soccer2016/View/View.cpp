// View.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include "View.h"

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
	img = cvCreateImage (cvSize(x, y), IPL_DEPTH_8U, 3);
	cvZero (img);
	cvNamedWindow (str, CV_WINDOW_AUTOSIZE);
	refresh();
}


View::~View(void)
{
}

void View::refresh(void)
{
	CvPoint p1,p2;
	p1.x = 0;
	p1.y = 0;
	p2.x = img->width;
	p2.y = img->height;
	cvRectangle(img,p1,p2,CV_RGB (0, 255, 0),CV_FILLED);
}

void View::drawfield(void)
{
	int lineSize = 1;
	CvPoint2D32f ptf1, ptf2;  
	CvPoint pt1,pt2;
	CvScalar rcolor;
	CvSize parc;
	int scale = cn->getScale();
	int goal = cn->getGoal();
	int wspace = cn->getSpace();
	int hspace = cn->getSpace();

	rcolor = CV_RGB (255,255,255);

	//soccer field
	ptf1.x = wspace;
	ptf1.y = hspace;
	ptf2.x = (float)img->width-wspace;
	ptf2.y = (float)img->height-hspace;
	pt1 = cvPointFrom32f(ptf1);
	pt2 = cvPointFrom32f(ptf2);
	cvRectangle (img, pt1, pt2, rcolor, lineSize , CV_AA, 0);
	//draw line
		//draw center line
	ptf1.x = (float)img->width/2;
	ptf1.y = hspace;
	ptf2.x = (float)img->width/2;
	ptf2.y = (float)img->height-hspace;
	pt1 = cvPointFrom32f(ptf1);
	pt2 = cvPointFrom32f(ptf2);
	cvLine (img, pt1, pt2, rcolor, lineSize, CV_AA, 0);

		//draw center circle
	ptf1.x = (float)img->width/2;
	ptf1.y = (float)img->height/2;
	pt1 = cvPointFrom32f(ptf1);
	cvCircle(img,pt1,scale*9.15,rcolor,lineSize , CV_AA, 0);
		//draw penalty area
	ptf1.x = wspace;
	ptf1.y = img->height/2-(goal*scale/2+16.5*scale);
	ptf2.x = wspace+(16.5*scale);
	ptf2.y = (float)img->height/2+(goal*scale/2+16.5*scale);
	pt1 = cvPointFrom32f(ptf1);
	pt2 = cvPointFrom32f(ptf2);
	cvRectangle (img, pt1, pt2, rcolor, lineSize , CV_AA, 0);
	ptf1.x = (float)img->width-(wspace+(16.5*scale));
	ptf1.y = (float)img->height/2-(goal*scale/2+16.5*scale);
	ptf2.x = (float)img->width-wspace;
	ptf2.y = (float)img->height/2+(goal*scale/2+16.5*scale);
	pt1 = cvPointFrom32f(ptf1);
	pt2 = cvPointFrom32f(ptf2);
	cvRectangle (img, pt1, pt2, rcolor, lineSize , CV_AA, 0);
		//draw goal area
	ptf1.x = wspace;
	ptf1.y = (float)img->height/2-(goal*scale/2+5.5*scale/2);
	ptf2.x = wspace+(5.5*scale);
	ptf2.y = (float)img->height/2+(goal*scale/2+5.5*scale/2);
	pt1 = cvPointFrom32f(ptf1);
	pt2 = cvPointFrom32f(ptf2);
	cvRectangle (img, pt1, pt2, rcolor,lineSize , CV_AA, 0);
	ptf1.x = (float)img->width-(wspace+(5.5*scale));
	ptf1.y = (float)img->height/2-(goal*scale/2+5.5*scale/2);
	ptf2.x = (float)img->width-wspace;
	ptf2.y = (float)img->height/2+(goal*scale/2+5.5*scale/2);
	pt1 = cvPointFrom32f(ptf1);
	pt2 = cvPointFrom32f(ptf2);
	cvRectangle (img, pt1, pt2, rcolor, lineSize , CV_AA, 0);
		//penalty arc
	ptf1.x = wspace+11*scale;
	ptf1.y = img->height/2;
	parc.height = 9.15*scale;
	parc.width = 9.15*scale;
	pt1 = cvPointFrom32f(ptf1);
	cvEllipse(img,pt1,parc,0,-53,53,rcolor,lineSize, CV_AA, 0);
	ptf1.x = img->width-(wspace+11*scale);
	ptf1.y = img->height/2;
	parc.height = 9.15*scale;
	parc.width = 9.15*scale;
	pt1 = cvPointFrom32f(ptf1);
	cvEllipse(img,pt1,parc,0,180-53,53+180,rcolor, lineSize, CV_AA, 0);
}

void View::show(void)
{
	for(int t=0;t<LOOP;t++){
		drawfield();
		drawBall(t);
		drawPlayers(t);
		cvShowImage(str, img);
		cvWaitKey(200);
		refresh();
	}
}

void View::drawBall(int t)
{
	CvPoint point;
	CvPoint2D32f p_ball;

	p_ball.x = ball->getX()[t];
	p_ball.y = ball->getY()[t];
	point = cvPointFrom32f(p_ball);

	cvCircle (img, point, ballSize, CV_RGB (255, 255, 0), CV_FILLED);
}

void View::drawPlayers(int t)
{
	CvPoint point;
	CvPoint2D32f p_player;
	CvFont font1;
	char* numS = new char[4];

	cvInitFont(&font1, CV_FONT_HERSHEY_SIMPLEX, 0.4, 0.4, 0, 1, 8);
	for(int n = 0; n < NUM-1; n++){
		p_player.x = playersList->getX()[n+t*(NUM-1)];
		p_player.y = playersList->getY()[n+t*(NUM-1)];
		point = cvPointFrom32f(p_player);
		sprintf_s(numS, sizeof(4), "%d", n);

		if(n <  (NUM-1)/2){
			cvCircle (img, point, playerSize, CV_RGB (255, 0, 0), CV_FILLED);
			cvPutText(img, numS, point, &font1, CV_RGB (255, 0, 0) );
		}else{
			cvCircle (img, point, playerSize, CV_RGB (0, 0, 255), CV_FILLED);
			cvPutText(img, numS, point, &font1, CV_RGB (0, 0, 255) );
		}
	}
	delete numS;
}
