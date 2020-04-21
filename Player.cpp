
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
	// Status�̍X�V�������s���B
	playerStatus = updateStatus(playerStatus);
	
	// �A�j���[�V�����̉��������s���B
	animation->update(playerStatus);

	//// ���̃A�N�V���������݂̏����ɂ���đI�����Ă����B
	// ���̃A�N�V�������i�[���Ă����ϐ��B
	playerAction _next;

	// ���̏�Ԃ��r���؂�ւ��n�j�܂��́A�r���؂�ւ��m�f���A�j���[�V�������I��������A�A�A�A�N�V�����؂�ւ�����\���B
	if (IsAction_canSwitching[IsAction] || 
		(!IsAction_canSwitching[IsAction] && animation->isEnd())) {

		// _next�֎��̃V�[�����擾����B
		_next = getNextAction();

		// ���݂̃A�N�V�����ƈقȂ�A�N�V���������̃A�N�V������������A�A�A
		if (IsAction != _next) {

			// �A�j���[�V�����I�u�W�F�N�g���X�V���A�I���B
			animation = switchingAnimation(_next);
			return;
		}
		
		// �r���؂�ւ��m�f���A�j���[�V�������I��������A����ɁA�����A�N�V���������͂��ꑱ���āACrouch�i���Ⴊ�ށj��������A�A�A
		// switchingAnimation()�����s�����Ɋ֐����I���B
		if (IsAction == Crouch)
			return;	
		
		// �����A�N�V���������͂��ꑱ���āA���݂̃A�j���[�V�������I��������Ƃ肠����Idling��Ԃɂɐݒ�
		// ���̃R�}�ł̏�L�̏���"_next = getNextAction();"�ōēx���̏�Ԃ��X�V�����̂œ��͂��ꑱ������A�N�V�����ōX�V�B
		if (animation->isEnd()) {

			animation = switchingAnimation(Idle);
			return;
		}
	}
}

void Player::draw()
{
	animation->draw();
}

/*!

*/

Define::Status Player::updateStatus(Define::Status _nowStatus)
{
	Define::Status _nextStatus = _nowStatus;

	switch (IsAction) {
	case Brake:
		break;
	case Crouch:
		break;
	case Damage:
		break;
	case Idle:
		break;
	case Jump_Fall:
		break;
	case Jump_Landing:
		break;
	case Jump_MidAir:
		break;
	case Jump_Up:
		break;
	case Run:
		if (playerStatus.directRight)
			_nextStatus._x += speed_run;
		else
			_nextStatus._x -= speed_run;
		break;
	case Walk:
		if (playerStatus.directRight)
			_nextStatus._x += speed_walk;
		else
			_nextStatus._x -= speed_walk;
		break;
	}

	return _nextStatus;
}

/*!
@biref �R���g���[���̓��͏�Ԃɂ���Ď��̃A�N�V������Ԃ��擾����BplayerStatus�̍X�V�͂����ł͍s��Ȃ��B��Ԃ����肷�鏈�������B
@date 2020/04/21/18:30
@author mimuro
*/
Player::playerAction Player::getNextAction()
{
	// Brake
	if (IsAction == Run) {
		// R
		if (playerStatus.directRight && !Controller::getIns()->getOnRight())
			return Brake;
		// L
		if (!playerStatus.directRight && !Controller::getIns()->getOnLeft()) 
			return Brake;
	}

	// Jump
	if (Controller::getIns()->getOn_A()) {
		return Jump_Up;
	}

	// Crouch
	if (Controller::getIns()->getOnDown()) {
		return Crouch;
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
		return make_shared <Animation>(imagePath::getIns()->unityChan_Crouch, playerStatus, 6, 99, true);
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

