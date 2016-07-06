// Main.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "..\Input\Input.h"

using namespace std;

int main(int argc, char* args[])
{
	Input *ip;
	if(argc == 3){
		ip = new Input(); 
	}else{
		ip = new Input(args[1], args[2]);
	}
	return 0;
}

