// View.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include "View.h"
using namespace cv;
using namespace cv::superres;

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
	string filename = "D:\\Video\\test.mp4";
	VideoCapture cap(filename);
	if(!cap.isOpened()) return;
	Mat frame, next;
	cap >> frame;
	Mat output = Mat::zeros(frame.size(), frame.type());
    while(true){
		cap >> next;
		output = createHist(frame);
		imshow("image", next);
		imshow("Mimage", output);
		if(!cap.isOpened()) break;
		frame = next.clone();
	    if(waitKey(30) >= 0) break;
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

void View::drawDelaunay(int t, Subdiv2D subdiv){
	vector<Vec4f> edgeList;
	int Linesize = 1;
		
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
			line( img, p1, p2, CV_RGB (0, 0, 255),Linesize,CV_AA,0);
		}
	}
}

Subdiv2D View::divideSurface(int time, type t){
	int i;
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

Mat View::createHist(Mat frame){
	vector<Mat> bgr_planes;
	split( frame, bgr_planes);
	int histSize = 128;
	float range[] = { 0, 256};
	const float* histRange = {range};
	bool uniform = true, accumulate = false;
	Mat b_hist, g_hist, r_hist;
	calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);
	int hist_w = 512; int hist_h = 512;
	int bin_w = cvRound( (double) hist_w/histSize );
	Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	for( int i = 1; i < histSize; i++ )
	{
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
		Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ), Scalar( 255, 0, 0), 2, 8, 0 );
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
		Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ), Scalar( 0, 255, 0), 2, 8, 0 );
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
		Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ), Scalar( 0, 0, 255), 2, 8, 0 );
	}
	return(histImage);
}
