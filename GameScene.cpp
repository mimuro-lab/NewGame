
/*!
@file GameScene.cpp
@brief GameScene�N���X���̃����o�ނ̒�`���s��CPP�t�@�C���B
@date 2020/04/16/19:58
@author mimuro
*/

#include "GameScene.h"

/*!
@brief �v���C���[�I�u�W�F�N�g�̍��W�X�V�A�A�j���[�V�����̏����Ȃǂ��s���Bnnnnnnnnnnn
@date 2020/04/21/12:36
@author mimuro
@callgraph
*/
void GameScene::update()
{
	
	ValidSelectWindow();
	counterUpdate();

	if (IsSelected())
		return;	
	
	// �Z���N�g�E�B���h�E�������u�Ԃ̂݃R���g���[���̍X�V���s���B���̏u�Ԃ̓R���g���[����push�i�����ꂽ�u�Ԃ̏�ԁj�͖����������B
	if(IsSelectWindow_Closed())
		Controller::getIns()->update();

	

	// �K���Z���N�g�E�B���h�E���J����Ă��Ȃ�����O��Ƃ���B�I�u�W�F�N�g�̎Q�ƃG���[���o��B
	player->update(stage);	

	// �X�e�[�W����
	stage->update(player->getShiftingState(), player->getStatus());
	
	enemy->update(stage, player->getShiftingState());

	enemy1->update(stage, player->getShiftingState());
	
	// player�ɂ��_���[�W�v�f�̐���
	damageObjs = player->generateDamageObj(damageObjs);

	// �_���[�W�v�f�̍X�V�B
	for (unsigned int i = 0; i < damageObjs.size(); i++) {
		damageObjs[i]->update(player->getShiftingState().x, player->getShiftingState().y);
	}

}

void GameScene::draw()
{
	DrawFormatString(10, 50, GetColor(255, 255, 255), "Game");
	
	player->draw();

	enemy->draw();
	enemy1->draw();

	stage->draw();

	for (unsigned int i = 0; i < damageObjs.size(); i++) {
		damageObjs[i]->draw();
	}

	SelectWindow::drawSelectWindow();
}
