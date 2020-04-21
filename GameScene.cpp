
/*!
@file GameScene.cpp
@brief GameScene�N���X���̃����o�ނ̒�`���s��CPP�t�@�C���B
@date 2020/04/16/19:58
@author mimuro
*/

#include "GameScene.h"

void GameScene::update()
{
	counterUpdate();
	ValidSelectWindow();

	if (IsSelected())
		return;	

	// �K���Z���N�g�E�B���h�E���J����Ă��Ȃ�����O��Ƃ���B�I�u�W�F�N�g�̎Q�ƃG���[���o��B
	player->update();
}

void GameScene::draw()
{
	DrawFormatString(10, 50, GetColor(255, 255, 255), "Game");
	player->draw();

	SelectWindow::drawSelectWindow();

}
