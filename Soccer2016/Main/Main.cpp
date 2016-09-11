// Main.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "..\View\View.h"

using namespace std;

int main(int argc, char* args[])
{
	Input *ip;
	if(true){
		ip = new Input(); 
	}else{
		ip = new Input(args[1], args[2]);
	}
	ip->installCoodinate();
	View *vw = new View(ip, "Soccer Window");
	BallController bc(ip->getBall(), ip->getPlayersList(), ip->getConstNum());
	GameController gc(ip->getBall(), &bc, ip->getConstNum());
	ConstNum::ConditionOfGame cog = gc.getCondition(ConstNum::progress, 1);
	for(int t=1;t<ip->getConstNum()->getLoop();t++){
		cout<<t<<": ";
		bc.ballcondition(t);
		bc.ballattribution(t);
		ConstNum::Right right = gc.getOff(t);
		if(right == ConstNum::Right::off_a){
			cout<<"OffA"<<endl;
			if(ConstNum::ConditionOfGame::progress == gc.getCondition(cog, t)){
				vw->show(bc, t);
			}
		}else{
			cout<<"OffB"<<endl;
		}
	}
	return 0;
}

