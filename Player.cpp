
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
void Player::update()
{

	animation->update(playerStatus);

	playerAction _next;

	if (IsAction_canSwitching[IsAction] || 
		(!IsAction_canSwitching[IsAction] && animation->isEnd())) {
		_next = updateStatus();
		if (IsAction != _next) {
			animation = switchingAnimation(_next);
			return;
		}
	}

	if (animation->isEnd())
		animation = switchingAnimation(Idle);
	
}

void Player::draw()
{
	animation->draw();
}

/*!
@biref �R���g���[���̓��͏�Ԃɂ���Ď��̃A�N�V������Ԃ��擾����BplayerStatus�̍X�V�͂����ł͍s��Ȃ��B��Ԃ����肷�鏈�������B
@date 2020/04/21/18:30
@author mimuro
*/
Player::playerAction Player::updateStatus()
{
	// Jump
	if (Controller::getIns()->getOn_A()) {
		return Jump_Up;
	}
	
	// Run R
	if (Controller::getIns()->getOn_B() && Controller::getIns()->getOnRight()) {
		playerStatus.directRight = true;
		return Run;
	}
	
	// Run L
	if (Controller::getIns()->getOn_B() && Controller::getIns()->getOnLeft()) {
		playerStatus.directRight = false;
		return Run;
	}

	// Walk R
	if (Controller::getIns()->getOnRight()) {
		playerStatus.directRight = true;
		return Walk;
	}

	// Walk L
	if (Controller::getIns()->getOnLeft()) {
		playerStatus.directRight = false;
		return Walk;
	}

	// �������͂���Ȃ����Idling��Ԃɂ���B
	return Idle;

}

/*!
@brief IsAction���X�V���āA���̃A�N�V������Animation�^�̃I�u�W�F�N�g��Ԃ��B
@date 2020/04/21/18:33
@author mimuro
*/
std::shared_ptr<Animation> Player::switchingAnimation(playerAction next)
{
	switch (next) {
	case Brake:
		IsAction = Brake;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Brake, playerStatus);
		break;
	case Crouch:
		IsAction = Crouch;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Crouch, playerStatus);
		break;
	case Damage:
		IsAction = Damage;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Damage, playerStatus);
		break;
	case Idle:
		IsAction = Idle;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Idle, playerStatus);
		break;
	case Jump_Fall:
		IsAction = Jump_Fall;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Fall, playerStatus);
		break;
	case Jump_Landing:
		IsAction = Jump_Landing;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Landing, playerStatus);
		break;
	case Jump_MidAir:
		IsAction = Jump_MidAir;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_MidAir, playerStatus);
		break;
	case Jump_Up:
		IsAction = Jump_Up;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Up, playerStatus);
		break;
	case Run:
		IsAction = Run;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Run, playerStatus);
		break;
	case Walk:
		IsAction = Walk;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Walk, playerStatus);
		break;
	}
}

