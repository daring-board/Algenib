// View.cpp : DLL �A�v���P�[�V�����p�ɃG�N�X�|�[�g�����֐����`���܂��B
//

#include "stdafx.h"
#include "View.h"




View::View(void)
{
}

View::View(Input *ip){
	cn = ip->getConstNum();
	//width, height�̉摜���쐬
	int x = cn->getFieldWidth()*cn->getScale()+2*cn->getSpace();
	int y = cn->getFieldHeight()*cn->getScale()+2*cn->getSpace();
	img = cvCreateImage (cvSize(x, y), IPL_DEPTH_8U, 3);
	cvZero (img);
}


View::~View(void)
{
}
