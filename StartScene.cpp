
/*!
@file StartScene.cpp
@brief StartScene�N���X���̃����o�ނ̒�`���s��CPP�t�@�C���B
@date 2020/04/16/20:01
@author mimuro
*/

#include "StartScene.h"

void StartScene::update()
{
	if (!SelectScene())
		;

	if (Controller::getIns()->getPush_A())
		GoNextScene();
}

void StartScene::draw()
{
	unsigned int gameTextColor, menuTextColor, configTextColor;

	gameTextColor = menuTextColor = configTextColor = GetColor(255, 255, 255);

	switch (nextSceneSelected) {
	case game:
		gameTextColor = GetColor(255, 0, 0);
		break;
	case menu:
		menuTextColor = GetColor(255, 0, 0);
		break;
	case config:
		configTextColor = GetColor(255, 0, 0);
		break;
	}
	DrawFormatString(50, 50, gameTextColor, "GAME");
	DrawFormatString(50, 70, menuTextColor, "MENU");
	DrawFormatString(50, 90, configTextColor, "CONF");
}


const bool StartScene::SelectScene()
{
	if (Controller::getIns()->getDown()) {
		nextSceneSelected++;
		nextSceneSelected %= _end;
		if (nextSceneSelected == none)
			nextSceneSelected = none + 1;
	}
	
	if (Controller::getIns()->getUp()) {
		nextSceneSelected--;
		nextSceneSelected %= _end;
		if (nextSceneSelected == none)
			nextSceneSelected = _end - 1;
	}

	return true;	
}

const bool StartScene::GoNextScene()
{
	switch (nextSceneSelected) {
	case game:
		changer->changeScene(eGameScene, false);
		break;
	case menu:
		changer->changeScene(eMenuScene, false);
		break;
	case config:
		changer->changeScene(eConfigScene, false);
		break;
	}

	return true;
}