
/*!
@file AnimationSwitch.cpp
@brief AnimationSwitch�N���X���̃����o�ނ̒�`���s��CPP�t�@�C���B
@date 2020/05/04/15:29
@author mimuro
*/

#include "AnimationSwitch.h"

/*!
@brief �R���g���[����A�j���[�V�����A�X�e�[�^�X�ⓖ���蔻��̏�Ԃ��玟�̃A�N�V������Ԃ��v�Z����B
@par �Ԃ��̂�Animation�^�̕ϐ��B
@date 2020/05/04/15:30
@author mimuro
*/
shared_ptr<Animation> AnimationSwitch::update(
	shared_ptr<CollisionDetect> collision, 
	shared_ptr<Animation> animation, 
	Status playerStatus)
{

	// �A�j���[�V������؂�ւ��Ă��悢�Ȃ�A
	if (acceptSwitching(animation, nowAction)) 
	{
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
			shared_ptr<Animation> returnAnimation = animation;
			returnAnimation->refreshing();
			return returnAnimation;
		}
	}

	return animation;

}

/*!
@brief �A�j���[�V������؂�ւ��Ă��ǂ����𔻒f����B
@par �A�j���[�V�������I������O�ɐ؂�ւ��Ă��悢��Ԃ��A�����łȂ��Ă��A�j���[�V�������I����������true��Ԃ��B
@date 2020/05/04/15:30
@author mimuro
*/
bool AnimationSwitch::acceptSwitching(shared_ptr<Animation> animation, rollAction_Basic nowAction)
{
	// ���̏�Ԃ��r���؂�ւ��n�j��������؂�ւ��n�j
	if (IsAction_canSwitching[static_cast<int>(nowAction)])
		return true;

	// �r���؂�ւ��m�f���A�j���[�V�������I��������؂�ւ��n�j
	if(!IsAction_canSwitching[static_cast<int>(nowAction)] && animation->isEnd())
		return true;

	return false;
}

/*!
@brief ���̏�Ԃ��󂯓���Ă悢���ǂ����𔻒f����B
@par ���̏�Ԃ����Ɠ�����������p���Ȃ̂Ő؂�ւ��������s��Ȃ��B�܂��AJump_MidAir�ł͑��x��������̎��͐؂�ւ��������s��Ȃ��B
@date 2020/05/04/15:43
@author mimuro
*/
bool AnimationSwitch::acceptNextAction(rollAction_Basic nowAction, rollAction_Basic nextAction, Status _playerStatus)
{
	// ���݂̃A�N�V�����Ɠ����A�N�V���������̃A�N�V������������؂�ւ��Ȃ��B
	if (nowAction == nextAction)
		return false;

	//Jump_MidAir�̎��́A���x������̊Ԃ̓A�j���[�V������؂�ւ��Ȃ��B
	if (nowAction == rollAction_Basic::Jump_MidAir && playerStatus._y_speed < 0)
		return false;

	// ��L�̏����ɓ��Ă͂܂�Ȃ��̂Ȃ�؂�ւ���B
	return true;
}

/*!
@brief �A�j���[�V���������t���b�V�����邩�ǂ������f����֐��B
@par ���Ⴊ�ށE�W�����v�i�󒆁j�A�A�j���[�V�������I�����Ă��Ȃ��Ȃ烊�t���b�V�����Ȃ��B����ȊO�Ȃ烊�t���b�V������B
@date 2020/05/04/15:48
@author mimuro
*/
bool AnimationSwitch::isRefresh(rollAction_Basic nowAction, shared_ptr<Animation> animation)
{
	// �r���؂�ւ��m�f���A�j���[�V�������I��������A����ɁA�����A�N�V���������͂��ꑱ���āACrouch�i���Ⴊ�ށj��������A�A�A
	// switchingAnimation()�����s�����Ɋ֐����I���B(refresh�����ɏI��)
	if (nowAction == rollAction_Basic::Crouch )
		return false;
	
	if (nowAction == rollAction_Basic::Jump_MidAir)
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
@date 2020/05/04/15:49
@author mimuro
*/
rollAction_Basic AnimationSwitch::getNextAction(
	shared_ptr<CollisionDetect> collision, 
	shared_ptr<Animation> animation, 
	Status playerStatus,
	rollAction_Basic nowAction)
{

	// Brake���I������狭���I�ɃA�C�h�����O��ԂɕύX����
	if (nowAction == rollAction_Basic::Brake && animation->isEnd()) {
		return rollAction_Basic::Idle;
	}

	// Jump_Up to Jump_MidAir
	if (nowAction == rollAction_Basic::Jump_Up && animation->isEnd()) {
		//printfDx("JumpUp to JumpMidAir\n");
		return rollAction_Basic::Jump_MidAir;
	}

	// Jump_MidAir to Fall
	if (nowAction == rollAction_Basic::Jump_MidAir && animation->isEnd()) {
		//printfDx("JumpMidAir to Fall\n");
		return rollAction_Basic::Fall;
	}

	// �W�����v���ɓ���ɏ�ǂ���������Fall�ɋ����ύX
	if (nowAction == rollAction_Basic::Jump_Up || nowAction == rollAction_Basic::Jump_MidAir) {
		if(collision->getCollisionedSide().head)
			return rollAction_Basic::Jump_Fall;
	}

	// Jump_Landing
	if (nowAction == rollAction_Basic::Fall && collision->getCollisionedSide().bottom) {
		//printfDx("Fall to Jump_Landing\n");
		return rollAction_Basic::Jump_Landing;
	}

	// �W�����v�ŕ����オ���Ă���Ƃ��ȊO�ŁA�����ɏ�ǂ��������Fall�ɋ����ύX
	if (nowAction != rollAction_Basic::Jump_Up && nowAction != rollAction_Basic::Jump_MidAir) {
		if (!collision->getCollisionedSide().bottom) {
			return rollAction_Basic::Fall;
		}
	}

	// Crouch��������́A�������n�ʂɂ��Ă��鎖
	if (Controller::getIns()->getOnDown() && collision->getCollisionedSide().bottom) {
		return rollAction_Basic::Crouch;
	}

	// Brake
	if (nowAction == rollAction_Basic::Run) {
		// R
		if (playerStatus.directRight && !Controller::getIns()->getOnRight())
			return rollAction_Basic::Brake;
		// L
		if (!playerStatus.directRight && !Controller::getIns()->getOnLeft())
			return rollAction_Basic::Brake;
	}

	// Jump��������́A�������n�ʂɂ��Ă��鎖
	if (Controller::getIns()->getPush_A() && collision->getCollisionedSide().bottom) {
		return rollAction_Basic::Jump_Up;
	}

	/// �������n�ʂɂ��Ă����ԂŁA�W�����v�Œn�ʂ�����グ���u�ԏo�Ȃ���
	if (collision->getCollisionedSide().bottom && nowAction != rollAction_Basic::Jump_Up) {
		// Run R
		if (Controller::getIns()->getOn_B() && Controller::getIns()->getOnRight()) {
			playerStatus.directRight = true;
			return rollAction_Basic::Run;
		}

		// Run L
		if (Controller::getIns()->getOn_B() && Controller::getIns()->getOnLeft()) {
			playerStatus.directRight = false;
			return rollAction_Basic::Run;
		}

		// Walk R
		if (Controller::getIns()->getOnRight()) {
			playerStatus.directRight = true;
			return rollAction_Basic::Walk;
		}

		// Walk L
		if (Controller::getIns()->getOnLeft()) {
			playerStatus.directRight = false;
			return rollAction_Basic::Walk;
		}
	}
	// �������͂���Ȃ����Idling��Ԃɂ���B

	if(nowAction != rollAction_Basic::Jump_Up && nowAction != rollAction_Basic::Jump_MidAir)
		return rollAction_Basic::Idle;

	return nowAction;

}

/*!
@brief IsAction���X�V���āA���̃A�N�V������Animation�^�̃I�u�W�F�N�g��Ԃ��B
@date 2020/05/04/15:49
@author mimuro
*/
shared_ptr<Animation> AnimationSwitch::switchingAnimation(rollAction_Basic next, Status nowStatus)
{
	using namespace std;
	switch (next) {
	case rollAction_Basic::Brake:
		nowAction = rollAction_Basic::Brake;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Brake, nowStatus);
		break;
	case rollAction_Basic::Crouch:
		nowAction = rollAction_Basic::Crouch;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Crouch, nowStatus);
		break;
	case rollAction_Basic::Damage:
		nowAction = rollAction_Basic::Damage;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Damage, nowStatus);
		break;
	case rollAction_Basic::Idle:
		nowAction = rollAction_Basic::Idle;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Idle, nowStatus);
		break;
	case rollAction_Basic::Jump_Fall:
		nowAction = rollAction_Basic::Jump_Fall;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Fall, nowStatus);
		break;
	case rollAction_Basic::Jump_Landing:
		nowAction = rollAction_Basic::Jump_Landing;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Landing, nowStatus);
		break;
	case rollAction_Basic::Jump_MidAir:
		nowAction = rollAction_Basic::Jump_MidAir;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_MidAir, nowStatus, 3, 99, true);
		break;
	case rollAction_Basic::Jump_Up:
		nowAction = rollAction_Basic::Jump_Up;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Up, nowStatus);
		break;
	case rollAction_Basic::Fall:
		nowAction = rollAction_Basic::Fall;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Fall, nowStatus);
		break;
	case rollAction_Basic::Run:
		nowAction = rollAction_Basic::Run;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Run, nowStatus);
		break;
	case rollAction_Basic::Walk:
		nowAction = rollAction_Basic::Walk;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Walk, nowStatus);
		break;
	}

	// �G���[�����A�����I������Ȃ��������荇�����A�C�h�����O��Ԃɂ���B
	return make_shared <Animation>(imagePath::getIns()->unityChan_Idle, nowStatus);
}
