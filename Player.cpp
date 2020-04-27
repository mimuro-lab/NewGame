
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

	// Status�̍X�V�������s���B
	playerStatus = animationMove->update(playerStatus, IsAction, collision, _stage, animation);

	// Collision�̍X�V���s���B
	collision->update(playerStatus, _stage);

	//// ���̃A�N�V���������݂̏����ɂ���đI�����Ă����B
	// ���̃A�N�V�������i�[���Ă����ϐ��B
	Define::rollAction_Basic _next;

	// �A�j���[�V�����̉��������s���B
	animation->update(playerStatus);
	
	// ���̏�Ԃ��r���؂�ւ��n�j�܂��́A�r���؂�ւ��m�f���A�j���[�V�������I��������A�A�A�A�N�V�����؂�ւ�����\���B
	if (IsAction_canSwitching[static_cast<int>(IsAction)] ||
		(!IsAction_canSwitching[static_cast<int>(IsAction)] && animation->isEnd())) {

		// _next�֎��̃V�[�����擾����B
		_next = getNextAction(collision, animation);
		
		// ���݂̃A�N�V�����ƈقȂ�A�N�V���������̃A�N�V������������A�A�A
		if (IsAction != _next) {
			//Jump_MidAir�̎��́A���x������̊Ԃ̓A�j���[�V������؂�ւ��Ȃ��B
			if (IsAction == Define::rollAction_Basic::Jump_MidAir && playerStatus._y_speed <= 0)
				return;
			// �A�j���[�V�����I�u�W�F�N�g���X�V���A�I���B
			animation = switchingAnimation(_next);
			return;
		}
		
		// �r���؂�ւ��m�f���A�j���[�V�������I��������A����ɁA�����A�N�V���������͂��ꑱ���āACrouch�i���Ⴊ�ށj��������A�A�A
		// switchingAnimation()�����s�����Ɋ֐����I���B
		if (IsAction == Define::rollAction_Basic::Crouch || IsAction == Define::rollAction_Basic::Jump_MidAir)
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
@biref �R���g���[���̓��͏�Ԃɂ���Ď��̃A�N�V������Ԃ��擾����BplayerStatus�̍X�V�͂����ł͍s��Ȃ��B��Ԃ����肷�鏈�������B
@date 2020/04/21/18:30
@author mimuro
*/
Define::rollAction_Basic Player::getNextAction(std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Animation> _animation)
{
	bool a = animation->isEnd();
	// Jump_Up to Jump_MidAir
	if (IsAction == Define::rollAction_Basic::Jump_Up && animation->isEnd()) {
		//printfDx("JumpUp to JumpMidAir\n");
		return Define::rollAction_Basic::Jump_MidAir;
	}

	// Jump_MidAir to Fall
	if (IsAction == Define::rollAction_Basic::Jump_MidAir && animation->isEnd()) {
		//printfDx("JumpMidAir to Fall\n");
		return Define::rollAction_Basic::Fall;
	}

	// Jump_Landing
	if (IsAction == Define::rollAction_Basic::Fall	&& _collision->getCollisionedSide().bottom) {
		//printfDx("Fall to Jump_Landing\n");
		return Define::rollAction_Basic::Jump_Landing;
	}

	// Fall
	if (!_collision->getCollisionedSide().bottom) {
		return Define::rollAction_Basic::Fall;
	}

	// Brake
	if (IsAction == Define::rollAction_Basic::Run) {
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
std::shared_ptr<Animation> Player::switchingAnimation(Define::rollAction_Basic next)
{

	switch (next) {
	case Define::rollAction_Basic::Brake:
		IsAction = Define::rollAction_Basic::Brake;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Brake, playerStatus);
		break;
	case Define::rollAction_Basic::Crouch:
		IsAction = Define::rollAction_Basic::Crouch;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Crouch, playerStatus);
		break;
	case Define::rollAction_Basic::Damage:
		IsAction = Define::rollAction_Basic::Damage;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Damage, playerStatus);
		break;
	case Define::rollAction_Basic::Idle:
		IsAction = Define::rollAction_Basic::Idle;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Idle, playerStatus);
		break;
	case Define::rollAction_Basic::Jump_Fall:
		IsAction = Define::rollAction_Basic::Jump_Fall;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Fall, playerStatus);
		break;
	case Define::rollAction_Basic::Jump_Landing:
		IsAction = Define::rollAction_Basic::Jump_Landing;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Landing, playerStatus);
		break;
	case Define::rollAction_Basic::Jump_MidAir:
		IsAction = Define::rollAction_Basic::Jump_MidAir;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_MidAir, playerStatus, 3, 99, true);
		break;
	case Define::rollAction_Basic::Jump_Up:
		IsAction = Define::rollAction_Basic::Jump_Up;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Jump_Up, playerStatus);
		break;
	case Define::rollAction_Basic::Fall:
		IsAction = Define::rollAction_Basic::Fall;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Fall, playerStatus);
		break;
	case Define::rollAction_Basic::Run:
		IsAction = Define::rollAction_Basic::Run;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Run, playerStatus);
		break;
	case Define::rollAction_Basic::Walk:
		IsAction = Define::rollAction_Basic::Walk;
		return make_shared <Animation>(imagePath::getIns()->unityChan_Walk, playerStatus);
		break;
	}

	// �G���[�����A�����I������Ȃ��������荇�����A�C�h�����O��Ԃɂ���B
	return make_shared <Animation>(imagePath::getIns()->unityChan_Idle, playerStatus);
}

