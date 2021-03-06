// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。
// Windows ヘッダー ファイル:
#include <windows.h>



// TODO: プログラムに必要な追加ヘッダーをここで参照してください。
#include "opencv2\opencv.hpp"
#include "opencv2\opencv_lib.hpp"
#include "..\Input\Input.h"
#include "..\Line\Line.h"
#include "..\BallController\BallController.h"
#include "..\GameController\GameController.h"
#include "..\TDA\TDA.h"
//#include "..\SPA\SPA.h"
#include "..\SPAD\SPAD.h"
#include "..\ParaCalcDom\ParaCalcDom.h"
#include "..\ParaPaintDom\ParaPaintDom.h"
#include <stack>
#include <sys/stat.h>