
/*!
@file StartScene.cpp
@brief StartScene�N���X���̃����o�ނ̒�`���s��CPP�t�@�C���B
@date 2020/04/16/20:01
@author mimuro
*/

#include "StartScene.h"

void StartScene::update()
{
	//changer->changeScene(eConfigScene, false);
}

void StartScene::draw()
{
	DrawFormatString(10, 70, GetColor(255, 255, 255), "StartScene");
}