
/*!
@file Player.cpp
@brief Player�N���X���̃����o�ނ̒�`���s��CPP�t�@�C���B
@date 2020/04/21/12:34
@author mimuro
*/

#include "Player.h"

/*!
@brief �v���C���[�I�u�W�F�N�g�̍��W�X�V�A�A�j���[�V�����̏����Ȃǂ��s���B
@date 2020/04/21/12:36
@author mimuro
*/
void Player::update(std::shared_ptr<Stage> _stage)
{
	// �v���C���[�̍��W�����肵�Ă��瓖���蔻�������B���������t�ɂ���ƃG���[�B
	// Collision�̍X�V���s���B
	collision->update(playerStatus, _stage);

	// Status�̍X�V�������s���B
	playerStatus = animationMove->update(playerStatus, animationSwitch->getNowAction(), collision, _stage, animation);

	// shiftingStage�̍X�V�������s���B
	shiftingStage = animationMove->getShiftingStage(collision, _stage);

	// �A�j���[�V�����̉��������s���B
	animation->update(playerStatus);
	
	// �A�j���[�V�����̐؂�ւ����s���B�����؂�ւ��Ȃ���Γ���animation�I�u�W�F�N�g��Ԃ��B
	animation = animationSwitch->update(collision, animation, playerStatus);

	// �������X�V����B
	playerStatus.directRight = playerDirect->updateDirect(animationSwitch->getNowAction(), playerStatus.directRight, playerStatus);

}

void Player::draw()
{
	animation->draw();
	//collision->draw();

}
