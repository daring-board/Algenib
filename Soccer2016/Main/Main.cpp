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
	View *vw = new View(ip, "Soccer Window");
	vw->drawfield();
	vw->show();
	return 0;
}

