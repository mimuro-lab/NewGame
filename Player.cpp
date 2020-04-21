
/*!
@file Player.cpp
@brief Player�N���X���̃����o�ނ̒�`���s��CPP�t�@�C���B
@date 2020/04/21/12:34
@author mimuro
*/

#include "Player.h"

Player::Player()
{
	playerStatus._x = Define::WIN_W / 2;
	playerStatus._y = Define::WIN_H / 2;
}

/*!
@brief �v���C���[�I�u�W�F�N�g�̍��W�X�V�A�A�j���[�V�����̏����Ȃǂ��s���B
@date 2020/04/21/12:36
@author mimuro
*/
void Player::update()
{
	if (Controller::getIns()->getOnRight()) {
		playerStatus._x += 1;
	}

	if (Controller::getIns()->getOnLeft()) {
		playerStatus._x -= 1;
	}

	animation->update(playerStatus._x, playerStatus._y);
	if (animation->isEnd()) {
		animation = std::make_shared<Animation>(imagePath::getIns()->unityChan_Idle, playerStatus._x, playerStatus._y);
	}
	
}

void Player::draw()
{
	animation->draw();
}