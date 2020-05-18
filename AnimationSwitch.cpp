
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

	soardCombContinue = getSoardComb(nowAction, animation, soardCombContinue);

	//DrawFormatString(100, 100, GetColor(255, 255, 255), "comb : %d", soardCombContinue);
	
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
bool AnimationSwitch::acceptSwitching(shared_ptr<Animation> animation, unityChan_Basic nowAction)
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
bool AnimationSwitch::acceptNextAction(unityChan_Basic nowAction, unityChan_Basic nextAction, Status _playerStatus)
{
	// ���݂̃A�N�V�����Ɠ����A�N�V���������̃A�N�V������������؂�ւ��Ȃ��B
	if (nowAction == nextAction)
		return false;

	//Jump_MidAir�̎��́A���x������̊Ԃ̓A�j���[�V������؂�ւ��Ȃ��B
	if (nowAction == unityChan_Basic::Jump_MidAir && playerStatus._y_speed < 0)
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
bool AnimationSwitch::isRefresh(unityChan_Basic nowAction, shared_ptr<Animation> animation)
{
	// �r���؂�ւ��m�f���A�j���[�V�������I��������A����ɁA�����A�N�V���������͂��ꑱ���āACrouch�i���Ⴊ�ށj��������A�A�A
	// switchingAnimation()�����s�����Ɋ֐����I���B(refresh�����ɏI��)
	if (nowAction == unityChan_Basic::Crouch )
		return false;
	
	if (nowAction == unityChan_Basic::Jump_MidAir)
		return false;

	// �����A�N�V���������͂��ꑱ���āA���݂̃A�j���[�V�������I�������猻�݂̃A�j���[�V���������t���b�V������B
	// �܂��A���̃R�}�ł̏�L�̏���"_next = getNextAction();"�ōēx���̏�Ԃ��X�V�����B
	if (!animation->isEnd())
		return false;

	// ��L�̏����ɓ��Ă͂܂�Ȃ��̂Ȃ烊�t���b�V������B
	return true;
}

bool AnimationSwitch::getSoardComb(unityChan_Basic nowAction, shared_ptr<Animation> animation, bool nowCombContinue)
{
	if (Controller::getIns()->getPush_X()) {
		if (nowAction == unityChan_Basic::Soard1_init)
			return true;
		if (nowAction == unityChan_Basic::Soard2_init)
			return true;
		if (nowAction == unityChan_Basic::Soard3_init)
			return true;
	}


	return nowCombContinue;
}

/*!
@biref �R���g���[���̓��͏�Ԃɂ���Ď��̃A�N�V������Ԃ��擾����BplayerStatus�̍X�V�͂����ł͍s��Ȃ��B��Ԃ����肷�鏈�������B
@date 2020/05/04/15:49
@author mimuro
*/
unityChan_Basic AnimationSwitch::getNextAction(
	shared_ptr<CollisionDetect> collision, 
	shared_ptr<Animation> animation, 
	Status playerStatus,
	unityChan_Basic nowAction)
{

	// Brake���I������狭���I�ɃA�C�h�����O��ԂɕύX����
	if (nowAction == unityChan_Basic::Brake && animation->isEnd()) {
		return unityChan_Basic::Idle;
	}

	// Jump_Up to Jump_MidAir
	if (nowAction == unityChan_Basic::Jump_Up && animation->isEnd()) {
		//printfDx("JumpUp to JumpMidAir\n");
		return unityChan_Basic::Jump_MidAir;
	}

	// Jump_MidAir to Fall
	if (nowAction == unityChan_Basic::Jump_MidAir && animation->isEnd()) {
		//printfDx("JumpMidAir to Fall\n");
		return unityChan_Basic::Fall;
	}

	// �W�����v���ɓ���ɏ�ǂ���������Fall�ɋ����ύX
	if (nowAction == unityChan_Basic::Jump_Up || nowAction == unityChan_Basic::Jump_MidAir) {
		if(collision->getCollisionedSide().head)
			return unityChan_Basic::Jump_Fall;
	}

	// Jump_Landing
	if (nowAction == unityChan_Basic::Fall && collision->getCollisionedSide().bottom) {
		//printfDx("Fall to Jump_Landing\n");
		return unityChan_Basic::Jump_Landing;
	}

	// �W�����v�ŕ����オ���Ă���Ƃ��ȊO�ŁA�����ɏ�ǂ��������Fall�ɋ����ύX
	if (nowAction != unityChan_Basic::Jump_Up && nowAction != unityChan_Basic::Jump_MidAir) {
		if (!collision->getCollisionedSide().bottom) {
			return unityChan_Basic::Fall;
		}
	}

	// Crouch��������́A�������n�ʂɂ��Ă��鎖
	if (Controller::getIns()->getOnDown() && collision->getCollisionedSide().bottom) {
		return unityChan_Basic::Crouch;
	}

	// Brake
	if (nowAction == unityChan_Basic::Run) {
		// R
		if (playerStatus.directRight && !Controller::getIns()->getOnRight())
			return unityChan_Basic::Brake;
		// L
		if (!playerStatus.directRight && !Controller::getIns()->getOnLeft())
			return unityChan_Basic::Brake;
	}

	// Jump��������́A�������n�ʂɂ��Ă��鎖
	if (Controller::getIns()->getPush_A() && collision->getCollisionedSide().bottom) {
		return unityChan_Basic::Jump_Up;
	}

	// ���U���R���{1
	if (nowAction == unityChan_Basic::Soard1_init) {

		// �R���{����Ȃ�A���̃R���{��Ԃ��B
		if (soardCombContinue) {
			soardCombContinue = false;
			return unityChan_Basic::Soard2_init;
			
		}

		// �R���{���Ȃ��Ȃ�soardCombContinue��false�ɂ��ďI���`��
		return unityChan_Basic::Soard1_end;

	}

	// ���U���R���{2
	if (nowAction == unityChan_Basic::Soard2_init) {

		// �R���{����Ȃ�A���̃R���{��Ԃ��B
		if (soardCombContinue) {
			soardCombContinue = false;
			return unityChan_Basic::Soard3_init;

		}

		// �R���{�𑱂��Ȃ��Ȃ�I���`��
		return unityChan_Basic::Soard1_end;
	}

	// ���U���R���{3
	if (nowAction == unityChan_Basic::Soard3_init) {

		// �R���{����Ȃ�A���̃R���{��Ԃ��B
		if (soardCombContinue) {
			soardCombContinue = false;
			return unityChan_Basic::Soard1_init;
		}

		// �R���{�𑱂��Ȃ��Ȃ�I���`��
		return unityChan_Basic::Soard1_end;
	}

	// �n���h�K���̌��������鏈��
	if (nowAction == unityChan_Basic::Hundgun_init || nowAction==unityChan_Basic::Hundgun_horizonal
		&& Controller::getIns()->getOn_Y()) {
		return unityChan_Basic::Hundgun_horizonal;
	}

	// �n���h�K����ł��I���鏈��
	if (nowAction == unityChan_Basic::Hundgun_horizonal) {
		return unityChan_Basic::Hundgun_end;
	}

	/// �������n�ʂɂ��Ă����ԂŁA�W�����v�Œn�ʂ�����グ���u�ԏo�Ȃ���
	if (collision->getCollisionedSide().bottom && nowAction != unityChan_Basic::Jump_Up) {

		// ���U���P�͂���
		if (Controller::getIns()->getOn_X())
			return unityChan_Basic::Soard1_init;

		// �n���h�K�������n��
		if (Controller::getIns()->getOn_Y())
			return unityChan_Basic::Hundgun_init;

		// Run R
		if (Controller::getIns()->getOn_B() && Controller::getIns()->getOnRight()) {
			playerStatus.directRight = true;
			return unityChan_Basic::Run;
		}

		// Run L
		if (Controller::getIns()->getOn_B() && Controller::getIns()->getOnLeft()) {
			playerStatus.directRight = false;
			return unityChan_Basic::Run;
		}

		// Walk R
		if (Controller::getIns()->getOnRight()) {
			playerStatus.directRight = true;
			return unityChan_Basic::Walk;
		}

		// Walk L
		if (Controller::getIns()->getOnLeft()) {
			playerStatus.directRight = false;
			return unityChan_Basic::Walk;
		}
	}

	// �������͂���Ȃ����Idling��Ԃɂ���B
	if (nowAction != unityChan_Basic::Jump_Up && nowAction != unityChan_Basic::Jump_MidAir) {

		return unityChan_Basic::Idle;
	}

	return nowAction;

}

/*!
@brief IsAction���X�V���āA���̃A�N�V������Animation�^�̃I�u�W�F�N�g��Ԃ��B
@date 2020/05/04/15:49
@author mimuro
*/
shared_ptr<Animation> AnimationSwitch::switchingAnimation(unityChan_Basic next, Status nowStatus)
{
	using namespace std;
	switch (next) {
	case unityChan_Basic::Brake:
		nowAction = unityChan_Basic::Brake;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Brake, nowStatus);
		break;
	case unityChan_Basic::Crouch:
		nowAction = unityChan_Basic::Crouch;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Crouch, nowStatus);
		break;
	case unityChan_Basic::Damage:
		nowAction = unityChan_Basic::Damage;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Damage, nowStatus);
		break;
	case unityChan_Basic::Idle:
		nowAction = unityChan_Basic::Idle;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Idle, nowStatus);
		break;
	case unityChan_Basic::Jump_Fall:
		nowAction = unityChan_Basic::Jump_Fall;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Fall, nowStatus);
		break;
	case unityChan_Basic::Jump_Landing:
		nowAction = unityChan_Basic::Jump_Landing;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Landing, nowStatus);
		break;
	case unityChan_Basic::Jump_MidAir:
		nowAction = unityChan_Basic::Jump_MidAir;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_MidAir, nowStatus, 3);
		break;
	case unityChan_Basic::Jump_Up:
		nowAction = unityChan_Basic::Jump_Up;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Up, nowStatus);
		break;
	case unityChan_Basic::Fall:
		nowAction = unityChan_Basic::Fall;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Fall, nowStatus);
		break;
	case unityChan_Basic::Run:
		nowAction = unityChan_Basic::Run;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Run, nowStatus);
		break;
	case unityChan_Basic::Walk:
		nowAction = unityChan_Basic::Walk;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Walk, nowStatus);
		break;
	case unityChan_Basic::Hundgun_init:
		nowAction = unityChan_Basic::Hundgun_init;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Hundgun_init, nowStatus, 0, -3, 3);
		break;
	case unityChan_Basic::Hundgun_end:
		nowAction = unityChan_Basic::Hundgun_end;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Hundgun_end, nowStatus, 0, -3, 5);
		break;
	case unityChan_Basic::Hundgun_horizonal:
		nowAction = unityChan_Basic::Hundgun_horizonal;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Hundgun_horizonal, nowStatus, 0, -3, 3);
		break;
	case unityChan_Basic::Soard1_init:
		nowAction = unityChan_Basic::Soard1_init;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Soard1_init, nowStatus, 0, -59, 3);
		break;
	case unityChan_Basic::Soard1_end:
		nowAction = unityChan_Basic::Soard1_end;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Soard1_end, nowStatus, 0, -59, 5);
		break;
	case unityChan_Basic::Soard2_init:
		nowAction = unityChan_Basic::Soard2_init;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Soard2_init, nowStatus, 0, -59, 3);
		break;
	case unityChan_Basic::Soard3_init:
		nowAction = unityChan_Basic::Soard3_init;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Soard3_init, nowStatus, 0, -59, 3);
		break;
	}

	// �G���[�����A�����I������Ȃ��������荇�����A�C�h�����O��Ԃɂ���B
	return make_shared <Animation>(imagePath::getIns()->unityChan_Idle, nowStatus);
}
