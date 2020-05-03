#pragma once

#include "CollisionDetect.h"
#include "Controller.h"
#include "Animation.h"
#include "Define.h"
#include "imagePath.h"
#include <memory>

class AnimationSwitch
{

	std::shared_ptr<Animation> _animation;

	//! �A�N�V�������ɑ��̃A�N�V�����ɐ؂�ւ��\���ǂ����H�i�Y������Define::rollAction_Basic�ɑΉ��j
	std::vector<bool> IsAction_canSwitching;

	//! �v���C���[�I�u�W�F�N�g�̌��݂̏�Ԃ��Ǘ��B
	Define::rollAction_Basic nowAction;

	//// ���̃A�N�V���������݂̏����ɂ���đI�����Ă����B
	// ���̃A�N�V�������i�[���Ă����ϐ��B
	Define::rollAction_Basic nextAction;

	//! �v���C���[�I�u�W�F�N�g�̍��W�Ȃǂ̏����܂Ƃ߂�I�u�W�F�N�g�B
	Define::Status playerStatus;


	bool acceptSwitching(std::shared_ptr<Animation> animation, Define::rollAction_Basic nowAction);

	bool acceptNextAction(Define::rollAction_Basic nowAction, Define::rollAction_Basic nextAction, Define::Status _playerStatus);

	bool isRefresh(Define::rollAction_Basic nowAction, std::shared_ptr<Animation> __animation);

	//! �R���g���[���̓��͂Ȃǂɉ��������̃A�N�V�������擾����B
	Define::rollAction_Basic getNextAction(
		std::shared_ptr<CollisionDetect> _collision, 
		std::shared_ptr<Animation> _animation, 
		Define::Status playerStatus,
		Define::rollAction_Basic nowAction);
	
	//! �A�j���[�V������؂�ւ���֐��B
	std::shared_ptr<Animation> switchingAnimation(Define::rollAction_Basic next, Define::Status _playerStatus);

public:
	AnimationSwitch()
	{ 
		nowAction = Define::rollAction_Basic::Fall;
		
		// IsAction_canSwitchin�̏������B Idle, Walk, Run, Fall�̏�Ԃ̂Ƃ��͐؂�ւ��\�̏�ԁB
		IsAction_canSwitching = std::vector<bool>(static_cast<int>(Define::rollAction_Basic::_end), false);

		IsAction_canSwitching[static_cast<int>(Define::rollAction_Basic::Idle)]
			= IsAction_canSwitching[static_cast<int>(Define::rollAction_Basic::Walk)]
			= IsAction_canSwitching[static_cast<int>(Define::rollAction_Basic::Run)]
			= IsAction_canSwitching[static_cast<int>(Define::rollAction_Basic::Fall)]
			= IsAction_canSwitching[static_cast<int>(Define::rollAction_Basic::Jump_Up)]
			= IsAction_canSwitching[static_cast<int>(Define::rollAction_Basic::Jump_MidAir)]
			= true;
	};
	~AnimationSwitch() = default;

	std::shared_ptr<Animation> update(
		std::shared_ptr<CollisionDetect> collision,
		std::shared_ptr<Animation> animation,
		Define::Status playerStatus);

	Define::rollAction_Basic getNowAction() { return nowAction; }

};

