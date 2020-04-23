
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
	// Collision�̍X�V���s���B
	collision->update(playerStatus, _stage);

	// Status�̍X�V�������s���B
	playerStatus = updateStatus(playerStatus, collision, _stage);
	
	// �A�j���[�V�����̉��������s���B
	animation->update(playerStatus);

	//// ���̃A�N�V���������݂̏����ɂ���đI�����Ă����B
	// ���̃A�N�V�������i�[���Ă����ϐ��B
	playerAction _next;

	// ���̏�Ԃ��r���؂�ւ��n�j�܂��́A�r���؂�ւ��m�f���A�j���[�V�������I��������A�A�A�A�N�V�����؂�ւ�����\���B
	if (IsAction_canSwitching[IsAction] || 
		(!IsAction_canSwitching[IsAction] && animation->isEnd())) {

		// _next�֎��̃V�[�����擾����B
		_next = getNextAction(collision, animation);

		// ���݂̃A�N�V�����ƈقȂ�A�N�V���������̃A�N�V������������A�A�A
		if (IsAction != _next) {

			// �A�j���[�V�����I�u�W�F�N�g���X�V���A�I���B
			animation = switchingAnimation(_next);
			return;
		}
		
		// �r���؂�ւ��m�f���A�j���[�V�������I��������A����ɁA�����A�N�V���������͂��ꑱ���āACrouch�i���Ⴊ�ށj��������A�A�A
		// switchingAnimation()�����s�����Ɋ֐����I���B
		if (IsAction == playerAction::Crouch)
			return;	
		
		// �����A�N�V���������͂��ꑱ���āA���݂̃A�j���[�V�������I�������猻�݂̃A�j���[�V���������t���b�V������B
		// �܂��A���̃R�}�ł̏�L�̏���"_next = getNextAction();"�ōēx���̏�Ԃ��X�V�����B
		if (animation->isEnd()) {
			animation->refreshing();
			return;
		}
	}


}

void Player::draw()
{
	animation->draw();
	collision->draw();
}

/*!

*/

Define::Status Player::updateStatus(Define::Status _nowStatus, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage)
{
	Define::Status _nextStatus = _nowStatus;

	switch (IsAction) {
	case playerAction::Brake:
		_nextStatus = animationMove->updateBrake(_nowStatus, _collision, _stage);
		break;
	case playerAction::Crouch:
		_nextStatus = animationMove->updateCrouch(_nowStatus, _collision, _stage);
		break;
	case playerAction::Damage:
		_nextStatus = animationMove->updateDamage(_nowStatus, _collision, _stage);
		break;
	case playerAction::Idle:
		_nextStatus = animationMove->updateIdle(_nowStatus, _collision, _stage);
		break;
	case playerAction::Jump_Fall:
		_nextStatus = animationMove->updateJump_Fall(_nowStatus, _collision, _stage);
		break;
	case playerAction::Jump_Landing:
		_nextStatus = animationMove->updateJump_Landing(_nowStatus, _collision, _stage);
		break;
	case playerAction::Jump_MidAir:
		_nextStatus = animationMove->updateJump_MidAir(_nowStatus, _collision, _stage);
		break;
	case playerAction::Jump_Up:
		_nextStatus = animationMove->updateJump_Up(_nowStatus, _collision, _stage);
		break;
	case playerAction::Fall:
		_nextStatus = animationMove->updateFall(_nowStatus, _collision, _stage);
		break;
	case playerAction::Run:
		_nextStatus = animationMove->updateRun(_nowStatus, _collision, _stage);
		break;
	case playerAction::Walk:
		_nextStatus = animationMove->updateWalk(_nowStatus, _collision, _stage);
	}

	return _nextStatus;
}

/*!
@biref �R���g���[���̓��͏�Ԃɂ���Ď��̃A�N�V������Ԃ��擾����BplayerStatus�̍X�V�͂����ł͍s��Ȃ��B��Ԃ����肷�鏈�������B
@date 2020/04/21/18:30
@author mimuro
*/
Player::playerAction Player::getNextAction(std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Animation> _animation)
{
	// Jump_MidAir
	if (IsAction == playerAction::Jump_Up && animation->isEnd()) {
		return playerAction::Jump_MidAir;
	}

	// Jump_Landing
	if (IsAction == playerAction::Fall && _collision->getCollisionedSide().bottom) {
		return playerAction::Jump_Landing;
	}

	// Fall
	if (!_collision->getCollisionedSide().bottom) {
		return playerAction::Fall;
	}

	// Brake
	if (IsAction == playerAction::Run) {
		// R
		if (playerStatus.directRight && !Controller::getIns()->getOnRight())
			return playerAction::Brake;
		// L
		if (!playerStatus.directRight && !Controller::getIns()->getOnLeft()) 
			return playerAction::Brake;
	}

	// Jump
	if (Controller::getIns()->getPush_A()) {
		return playerAction::Jump_Up;
	}


	// Crouch
	if (Controller::getIns()->getOnDown()) {
		return playerAction::Crouch;
	}

	// Run R
	if (Controller::getIns()->getOn_B() && Controller::getIns()->getOnRight()) {
		playerStatus.directRight = true;
		return playerAction::Run;
	}
	
	// Run L
	if (Controller::getIns()->getOn_B() && Controller::getIns()->getOnLeft()) {
		playerStatus.directRight = false;
		return playerAction::Run;
	}

	// Walk R
	if (Controller::getIns()->getOnRight()) {
		playerStatus.directRight = true;
		return playerAction::Walk;
	}

	// Walk L
	if (Controller::getIns()->getOnLeft()) {
		playerStatus.directRight = false;
		return playerAction::Walk;
	}

	// �������͂���Ȃ����Idling��Ԃɂ���B
	return playerAction::Idle;

}

/*!
@brief IsAction���X�V���āA���̃A�N�V������Animation�^�̃I�u�W�F�N�g��Ԃ��B
@date 2020/04/21/18:33
@author mimuro
*/
std::shared_ptr<Animation> Player::switchingAnimation(playerAction next)
{

	switch (next) {
	case playerAction::Brake:
		IsAction = playerAction::Brake;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Brake, playerStatus);
		break;
	case playerAction::Crouch:
		IsAction = playerAction::Crouch;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Crouch, playerStatus, 6, 99, true);
		break;
	case playerAction::Damage:
		IsAction = playerAction::Damage;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Damage, playerStatus);
		break;
	case playerAction::Idle:
		IsAction = playerAction::Idle;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Idle, playerStatus);
		break;
	case playerAction::Jump_Fall:
		IsAction = playerAction::Jump_Fall;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Fall, playerStatus);
		break;
	case playerAction::Jump_Landing:
		IsAction = playerAction::Jump_Landing;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Landing, playerStatus);
		break;
	case playerAction::Jump_MidAir:
		IsAction = playerAction::Jump_MidAir;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_MidAir, playerStatus);
		break;
	case playerAction::Jump_Up:
		IsAction = playerAction::Jump_Up;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Up, playerStatus);
		break;
	case playerAction::Fall:
		IsAction = playerAction::Fall;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Fall, playerStatus);
		break;
	case playerAction::Run:
		IsAction = playerAction::Run;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Run, playerStatus);
		break;
	case playerAction::Walk:
		IsAction = playerAction::Walk;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Walk, playerStatus);
		break;
	}

	// �G���[�����A�����I������Ȃ��������荇�����A�C�h�����O��Ԃɂ���B
	return make_shared <Animation>(imagePath::getIns()->unityChan_Idle, playerStatus);
}

