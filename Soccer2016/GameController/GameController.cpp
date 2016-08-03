// GameController.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//
#include "stdafx.h"
#include "GameController.h"

ConstNum::ConditionOfGame GameController::sus_or(int moment){
	CvPoint2D32f tmp_ball;
	tmp_ball.x = ball->getX()[moment];
	tmp_ball.y = ball->getY()[moment];
	//cout<<ball.x<<","<<ball.y<<endl;
	if(in_field(tmp_ball)==1){
		if(bc->ballcondition(moment) == ConstNum::mix_up){
			int i=moment+1;
			while(bc->ballcondition(i) == ConstNum::mix_up){
				if(on_FK(tmp_ball,i)==1){
					return(ConstNum::suspend);
				}
				i++;
			}
		}

		if((bc->ballcondition(moment) == ConstNum::others)
			||(bc->ballcondition(moment) == ConstNum::mix_up)){
			int i=moment+1;
			while(bc->ballcondition(i) != ConstNum::others&&i<LOOP){
				i++;
			}
			if(excepteness(i)==1){
				return(ConstNum::suspend);
			}
		}
		return(ConstNum::progress);
	}

	//cout<<"6"<<endl;
	return(ConstNum::suspend);
}

ConstNum::ConditionOfGame GameController::pro_or(int moment){
	CvPoint2D32f tmp_ball;
	tmp_ball.x = ball->getX()[moment];
	tmp_ball.y = ball->getY()[moment];
	if(in_field(tmp_ball)==0){
		return(ConstNum::suspend);
	}

	tmp_ball.x = ball->getX()[moment+1];
	tmp_ball.y = ball->getY()[moment+1];
	if(bc->ballcondition(moment+1) == ConstNum::shot 
		&& bc->ballcondition(moment+2)==ConstNum::shot 
		&& bc->ballcondition(moment)!=ConstNum::others){
	//if(players->ballspeed(moment+1)>restartshot && players->ballspeed(moment+2)>restartshot && players->ballcondition(moment)!=others){
		if(in_field(tmp_ball)){
			if(!in_goalaria(tmp_ball)){
				return(ConstNum::progress);
			}
		}
	}
	return(ConstNum::suspend);
}

int GameController::in_goalaria(CvPoint2D32f b){
	if(wspace <= b.x && b.x <= wspace+(5.5*scale)){
		if((FIELD_height*scale+2*hspace)/2-(goal*scale/2+5.5*scale)<=b.y && b.y <=(FIELD_height*scale+2*hspace)/2+(goal*scale/2+5.5*scale)){
			return(1);
		}
	}

	if(FIELD_width*scale+wspace-(5.5*scale)<=b.x && b.x <= FIELD_width*scale+wspace){
		if((FIELD_height*scale+2*hspace)/2-(goal*scale/2+5.5*scale)<=b.y && b.y <=(FIELD_height*scale+2*hspace)/2+(goal*scale/2+5.5*scale)){
			return(1);
		}
	}

	return(0);
}

int GameController::in_field(CvPoint2D32f b){
	if(wspace <=b.x && b.x <= wspace+FIELD_width*scale){
		if(hspace-3*scale <=b.y && b.y <= hspace+(FIELD_height)*scale){
			return(1);
		}
	}
	return(0);
}

int GameController::on_FK(CvPoint2D32f b,int moment){
	if(stillness(b,moment)==1){
		return(1);
	}
	return(0);
}

int GameController::stillness(CvPoint2D32f b,int moment){
	CvPoint2D32f ball_p;
	for(int i=moment;i<moment+BALLstop;i++){
		ball_p.x = ball->getX()[i];
		ball_p.y = ball->getY()[i];
		//if(ball.x != players->getpoint(i)[0].x&&ball.y != players->getpoint(i)[0].y){
		if(((b.x-ball_p.x)*(b.x-ball_p.x)+(b.y-ball_p.y)*(b.y-ball_p.y)) >= DELT*DELT){
			return(0);
		}
	}
	return(1);
}

int GameController::excepteness(int moment){
	//CvPoint2D32f ball_p;
	for(int i=moment;i<moment+2*BALLstop;i++){
		if(bc->ballcondition(i)!=ConstNum::others){
			return(0);
		}
	}
	return(1);
}

ConstNum::Right GameController::isOff(int l,int m){
	if(((bc->ballattribution(l) == ConstNum::Attribution::own_a)&&
		(bc->ballattribution(m) == ConstNum::Attribution::own_a))||
		((bc->ballattribution(l) == ConstNum::Attribution::own_b)&&
		(bc->ballattribution(m) == ConstNum::Attribution::own_a))){
	//if(((players->ballattribution(l)==teamB)&&(players->ballattribution(m)==teamB)) || ((players->ballattribution(l)==teamB)&&(players->ballattribution(m)==teamA))){
		//return(Boff);
			return(ConstNum::Right::off_a);
	}else{
		//return(Aoff);
		return(ConstNum::Right::off_b);
	}
}

GameController::GameController(Ball *b, BallController *ballCon, ConstNum *cn){
	ball = b;
	bc = ballCon;
	LOOP = cn->getLoop();
	wspace = cn->getSpace();
	hspace = cn->getSpace();
	FIELD_height = cn->getFieldHeight();
	FIELD_width = cn->getFieldWidth();
	scale = cn->getScale();
	goal = cn->getGoal();
	BALLstop = cn->getBallStop();
	DELT = cn->getDelta()*scale;
}

ConstNum::ConditionOfGame GameController::getCondition(ConstNum::ConditionOfGame condition,int k){
	if(k==LOOP){
		return(condition);
	}else if(condition == ConstNum::progress){
		//cout<<"3"<<endl;
		return(sus_or(k));
	}else{
		//cout<<"4"<<endl;
		return(pro_or(k));
	}
}

ConstNum::Right GameController::getOff(int loop){
	ConstNum::Right offense;
	int l=loop,m=loop;

	if(bc->ballattribution(loop) == ConstNum::Attribution::own_w){
		while((bc->ballattribution(l) == ConstNum::Attribution::own_w)){
			l--;
		}
		while((bc->ballattribution(m) == ConstNum::Attribution::own_w)&&(m<LOOP)){
			m++;
		}
		offense=isOff(l,m);
		//offense=graviOff(loop,players);
		//offense = earlyOff(players,loop);
		//offense = nearOff(players,loop);
	}else{
		if(bc->ballattribution(loop) == ConstNum::Attribution::own_a){
			offense = ConstNum::Right::off_a;
		}else{
			offense = ConstNum::Right::off_b;
		}
	}
	return(offense);
}
