
/*!
@file MenuScene.cpp
@brief MenuScene�N���X���̃����o�ނ̒�`���s��CPP�t�@�C���B
@date 2020/04/16/03:02
@author mimuro
*/

#include "MenuScene.h"

void MenuScene::update()
{
	//changer->changeScene(eStartScene, false);
	SelectScene();
}

void MenuScene::draw()
{
	DrawFormatString(10,30,GetColor(255,255,255), "MenuScene");
}

void MenuScene::SelectScene()
{
	if (Controller::getIns()->getStart()) {
		changer->changeScene(eStartScene, false);
	}
}