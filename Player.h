
/*!
@file Player.h
@brief Player�N���X����`����Ă���w�b�_�t�@�C��
@date 2020/04/21/12:26
@author mimuro
*/

#pragma once
#include <DxLib.h>
#include "Define.h"
#include "imagePath.h"
#include "Controller.h"
#include "Animation.h"
#include "AnimationMove.h"
#include "CollisionDetect.h"
#include "Stage.h"
#include <memory>

/*!
@class Player
@brief Player�L�����̏����S�ʂ�S���N���X�B
@date 2020/04/21/12:28
@author mimuro
*/
class Player
{

	//! �������x
	char maxSpeed_walk = 5;
	//! ���鑬�x
	char maxSpeed_run = 10;
	//! Jump_Up�̏����x
	char jumpUp_initSpeed = 20;
	//! Jump_MidAir�̏����x
	char jumpMid_initSpeed = 15;

	//! �v���C���[�I�u�W�F�N�g�̌��݂̏�Ԃ��Ǘ��B
	Define::rollAction_Basic IsAction;

	//! �A�N�V�������ɑ��̃A�N�V�����ɐ؂�ւ��\���ǂ����H�i�Y������Define::rollAction_Basic�ɑΉ��j
	std::vector<bool> IsAction_canSwitching;

	//! �v���C���[�I�u�W�F�N�g�̍��W�Ȃǂ̏����܂Ƃ߂�I�u�W�F�N�g�B
	Define::Status playerStatus;

	//! �A�j���[�V�����̏������܂Ƃ߂čs���I�u�W�F�N�g�B
	std::shared_ptr<Animation> animation;

	//! �A�j���[�V��������Status�̍��W�̍X�V������I�u�W�F�N�g�B
	std::shared_ptr<AnimationMove> animationMove;

	//! �v���C���[�I�u�W�F�N�g�̓����蔻�菈�����܂Ƃ߂čs���I�u�W�F�N�g�B
	std::shared_ptr<CollisionDetect> collision;

	//! �A�j���[�V������؂�ւ���֐��B
	std::shared_ptr<Animation> switchingAnimation(Define::rollAction_Basic next);

	//! �R���g���[���̓��͂Ȃǂɉ��������̃A�N�V�������擾����B
	Define::rollAction_Basic getNextAction(std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Animation> _animation);

public:

	Player(std::shared_ptr<Stage> _stage) : 
		IsAction(Define::rollAction_Basic::Idle)
	{
		// �������̐ݒ�B
		playerStatus._x = Define::WIN_W / 2;
		playerStatus._y = Define::WIN_H / 2;

		playerStatus.directRight = true;

		// IsAction_canSwitchin�̏������B Idle, Walk, Run, Fall�̏�Ԃ̂Ƃ��͐؂�ւ��\�̏�ԁB
		IsAction_canSwitching = std::vector<bool>(static_cast<int>(Define::rollAction_Basic::_end), false);

		IsAction_canSwitching[static_cast<int>(Define::rollAction_Basic::Idle)]
			= IsAction_canSwitching[static_cast<int>(Define::rollAction_Basic::Walk)]
			= IsAction_canSwitching[static_cast<int>(Define::rollAction_Basic::Run)]
			= IsAction_canSwitching[static_cast<int>(Define::rollAction_Basic::Fall)]
			= true;

		animation = std::make_shared<Animation>(imagePath::getIns()->unityChan_Idle, playerStatus);

		animationMove = std::make_shared<AnimationMove>(maxSpeed_walk, maxSpeed_run, jumpUp_initSpeed, jumpMid_initSpeed);

		collision = std::make_shared<CollisionDetect>(_stage, playerStatus);

	};

	~Player() = default;

	//! Player�I�u�W�F�N�g�̑O�����S�ʂ��s���֐��B
	void update(std::shared_ptr<Stage> _stage);

	//! Player�I�u�W�F�N�g�̕`�揈���S�ʂ��s���֐��B
	void draw();
};
