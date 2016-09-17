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
	ConstNum::Right right;
	for(int t=1;t<ip->getConstNum()->getLoop();t++){
		vw->show(bc, t);
	}
	return 0;
}

