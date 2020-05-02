#include "AnimationSwitch.h"

std::shared_ptr<Animation> AnimationSwitch::update(
	std::shared_ptr<CollisionDetect> collision, 
	std::shared_ptr<Animation> animation, 
	Define::Status playerStatus)
{

	// �A�j���[�V������؂�ւ��Ă��悢�Ȃ�A
	if (acceptSwitching(animation, nowAction)) {
		// _next�֎��̃V�[�����擾����B
		nextAction = getNextAction(collision, animation, playerStatus, nowAction);
		if(acceptNextAction(nowAction, nextAction, playerStatus)) {
			// �A�j���[�V�����I�u�W�F�N�g���X�V���A�I���B
			nowAction = nextAction;
			return switchingAnimation(nextAction, playerStatus);
		}

		// �r���؂�ւ��m�f���A�j���[�V�������I��������A����ɁA�����A�N�V���������͂��ꑱ���āACrouch�i���Ⴊ�ށj��������A�A�A
		// switchingAnimation()�����s�����Ɋ֐����I���B(refresh�����ɏI��)
		if (isRefresh(nextAction, animation)) {
			std::shared_ptr<Animation> returnAnimation = animation;
			returnAnimation->refreshing();
			return returnAnimation;
		}
	}

	return animation;

}

bool AnimationSwitch::acceptSwitching(std::shared_ptr<Animation> animation, Define::rollAction_Basic nowAction)
{
	// ���̏�Ԃ��r���؂�ւ��n�j��������؂�ւ��n�j
	if (IsAction_canSwitching[static_cast<int>(nowAction)])
		return true;

	// �r���؂�ւ��m�f���A�j���[�V�������I��������؂�ւ��n�j
	if(!IsAction_canSwitching[static_cast<int>(nowAction)] && animation->isEnd())
		return true;

	return false;
}

bool AnimationSwitch::acceptNextAction(Define::rollAction_Basic nowAction, Define::rollAction_Basic nextAction, Define::Status _playerStatus)
{

	// ���݂̃A�N�V�����Ɠ����A�N�V���������̃A�N�V������������؂�ւ��Ȃ��B
	if (nowAction == nextAction)
		return false;

	//Jump_MidAir�̎��́A���x������̊Ԃ̓A�j���[�V������؂�ւ��Ȃ��B
	if (nowAction == Define::rollAction_Basic::Jump_MidAir && playerStatus._y_speed < 0)
		return false;

	// ��L�̏����ɓ��Ă͂܂�Ȃ��̂Ȃ�؂�ւ���B
	return true;
}

bool AnimationSwitch::isRefresh(Define::rollAction_Basic nowAction, std::shared_ptr<Animation> animation)
{
	// �r���؂�ւ��m�f���A�j���[�V�������I��������A����ɁA�����A�N�V���������͂��ꑱ���āACrouch�i���Ⴊ�ށj��������A�A�A
	// switchingAnimation()�����s�����Ɋ֐����I���B(refresh�����ɏI��)
	if (nowAction == Define::rollAction_Basic::Crouch )
		return false;
	
	if (nowAction == Define::rollAction_Basic::Jump_MidAir)
		return false;

	// �����A�N�V���������͂��ꑱ���āA���݂̃A�j���[�V�������I�������猻�݂̃A�j���[�V���������t���b�V������B
	// �܂��A���̃R�}�ł̏�L�̏���"_next = getNextAction();"�ōēx���̏�Ԃ��X�V�����B
	if (!animation->isEnd())
		return false;

	// ��L�̏����ɓ��Ă͂܂�Ȃ��̂Ȃ烊�t���b�V������B
	return true;
}

/*!
@biref �R���g���[���̓��͏�Ԃɂ���Ď��̃A�N�V������Ԃ��擾����BplayerStatus�̍X�V�͂����ł͍s��Ȃ��B��Ԃ����肷�鏈�������B
@date 2020/04/21/18:30
@author mimuro
*/
Define::rollAction_Basic AnimationSwitch::getNextAction(
	std::shared_ptr<CollisionDetect> collision, 
	std::shared_ptr<Animation> animation, 
	Define::Status playerStatus,
	Define::rollAction_Basic nowAction)
{

	// Jump_Up to Jump_MidAir
	if (nowAction == Define::rollAction_Basic::Jump_Up && animation->isEnd()) {
		//printfDx("JumpUp to JumpMidAir\n");
		return Define::rollAction_Basic::Jump_MidAir;
	}

	// Jump_MidAir to Fall
	if (nowAction == Define::rollAction_Basic::Jump_MidAir && animation->isEnd()) {
		//printfDx("JumpMidAir to Fall\n");
		return Define::rollAction_Basic::Fall;
	}

	// Jump_Landing
	if (nowAction == Define::rollAction_Basic::Fall && collision->getCollisionedSide().bottom) {
		//printfDx("Fall to Jump_Landing\n");
		return Define::rollAction_Basic::Jump_Landing;
	}

	// Fall
	if (!collision->getCollisionedSide().bottom) {
		return Define::rollAction_Basic::Fall;
	}

	// Brake
	if (nowAction == Define::rollAction_Basic::Run) {
		// R
		if (playerStatus.directRight && !Controller::getIns()->getOnRight())
			return Define::rollAction_Basic::Brake;
		// L
		if (!playerStatus.directRight && !Controller::getIns()->getOnLeft())
			return Define::rollAction_Basic::Brake;
	}

	// Jump
	if (Controller::getIns()->getPush_A()) {
		return Define::rollAction_Basic::Jump_Up;
	}


	// Crouch
	if (Controller::getIns()->getOnDown()) {
		return Define::rollAction_Basic::Crouch;
	}

	// Run R
	if (Controller::getIns()->getOn_B() && Controller::getIns()->getOnRight()) {
		playerStatus.directRight = true;
		return Define::rollAction_Basic::Run;
	}

	// Run L
	if (Controller::getIns()->getOn_B() && Controller::getIns()->getOnLeft()) {
		playerStatus.directRight = false;
		return Define::rollAction_Basic::Run;
	}

	// Walk R
	if (Controller::getIns()->getOnRight()) {
		playerStatus.directRight = true;
		return Define::rollAction_Basic::Walk;
	}

	// Walk L
	if (Controller::getIns()->getOnLeft()) {
		playerStatus.directRight = false;
		return Define::rollAction_Basic::Walk;
	}

	// �������͂���Ȃ����Idling��Ԃɂ���B
	return Define::rollAction_Basic::Idle;

}

/*!
@brief IsAction���X�V���āA���̃A�N�V������Animation�^�̃I�u�W�F�N�g��Ԃ��B
@date 2020/04/21/18:33
@author mimuro
*/
std::shared_ptr<Animation> AnimationSwitch::switchingAnimation(Define::rollAction_Basic next, Define::Status nowStatus)
{
	using namespace std;
	switch (next) {
	case Define::rollAction_Basic::Brake:
		nowAction = Define::rollAction_Basic::Brake;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Brake, nowStatus);
		break;
	case Define::rollAction_Basic::Crouch:
		nowAction = Define::rollAction_Basic::Crouch;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Crouch, nowStatus);
		break;
	case Define::rollAction_Basic::Damage:
		nowAction = Define::rollAction_Basic::Damage;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Damage, nowStatus);
		break;
	case Define::rollAction_Basic::Idle:
		nowAction = Define::rollAction_Basic::Idle;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Idle, nowStatus);
		break;
	case Define::rollAction_Basic::Jump_Fall:
		nowAction = Define::rollAction_Basic::Jump_Fall;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Fall, nowStatus);
		break;
	case Define::rollAction_Basic::Jump_Landing:
		nowAction = Define::rollAction_Basic::Jump_Landing;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Landing, nowStatus);
		break;
	case Define::rollAction_Basic::Jump_MidAir:
		nowAction = Define::rollAction_Basic::Jump_MidAir;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_MidAir, nowStatus, 3, 99, true);
		break;
	case Define::rollAction_Basic::Jump_Up:
		nowAction = Define::rollAction_Basic::Jump_Up;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Up, nowStatus);
		break;
	case Define::rollAction_Basic::Fall:
		nowAction = Define::rollAction_Basic::Fall;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Fall, nowStatus);
		break;
	case Define::rollAction_Basic::Run:
		nowAction = Define::rollAction_Basic::Run;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Run, nowStatus);
		break;
	case Define::rollAction_Basic::Walk:
		nowAction = Define::rollAction_Basic::Walk;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Walk, nowStatus);
		break;
	}

	// �G���[�����A�����I������Ȃ��������荇�����A�C�h�����O��Ԃɂ���B
	return make_shared <Animation>(imagePath::getIns()->unityChan_Idle, nowStatus);
}
