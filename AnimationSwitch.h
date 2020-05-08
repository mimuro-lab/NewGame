
/*!
@file AnimationSwitch.h
@brief AnimationSwitch�N���X����`����Ă���w�b�_�t�@�C��
@date 2020/05/04/15:03
@author mimuro
*/

#pragma once
#include "CollisionDetect.h"
#include "Controller.h"
#include "Animation.h"
#include "Define.h"
#include "imagePath.h"
#include <memory>

/*!
@class AnimationSwitch
@brief �A�j���[�V�����̏�Ԃ�؂�ւ���ׂ̃N���X
@date 2020/05/04/15:03
@author mimuro
*/

using namespace Define;
using namespace std;

class AnimationSwitch
{

	//! �A�j���[�V�����̐؂�ւ��ɂ́A�A�j���[�V�����̏�Ԃ��󂯎��K�v������B
	shared_ptr<Animation> _animation;

	//! �A�N�V�������ɑ��̃A�N�V�����ɐ؂�ւ��\���ǂ����H�i�Y������rollAction_Basic�ɑΉ��j
	vector<bool> IsAction_canSwitching;

	//! �v���C���[�I�u�W�F�N�g�̌��݂̏�Ԃ��Ǘ��B
	rollAction_Basic nowAction;

	//// ���̃A�N�V���������݂̏����ɂ���đI�����Ă����B
	//! ���̃A�N�V�������i�[���Ă����ϐ��B
	rollAction_Basic nextAction;

	//! �v���C���[�I�u�W�F�N�g�̍��W�Ȃǂ̏����܂Ƃ߂�I�u�W�F�N�g�B
	Status playerStatus;

	//! �A�N�V������Ԃ�؂�ւ��Ă��悢����Ԃ��B
	bool acceptSwitching(shared_ptr<Animation> animation, rollAction_Basic nowAction);

	//! �R���g���[���̓��͂Ȃǂɉ��������̃A�N�V�������擾����B
	rollAction_Basic getNextAction(
		shared_ptr<CollisionDetect> _collision, 
		shared_ptr<Animation> _animation, 
		Status playerStatus,
		rollAction_Basic nowAction);
	
	//! getNextAction�ɂ�蓾�����̃A�N�V������Ԃ�K������Ă悢���ǂ�����Ԃ��֐��B
	bool acceptNextAction(rollAction_Basic nowAction, rollAction_Basic nextAction, Status _playerStatus);

	//! animation�����t���b�V�����Ă��悢�����f����֐��B
	bool isRefresh(rollAction_Basic nowAction, shared_ptr<Animation> __animation);
	
	//! �A�j���[�V������؂�ւ���֐��B
	shared_ptr<Animation> switchingAnimation(rollAction_Basic next, Status _playerStatus);

public:
	AnimationSwitch()
	{ 
		// nowAction�͍ŏ��AFall����n�߂�B
		nowAction = rollAction_Basic::Fall;
		
		// IsAction_canSwitchin�̏������B Idle, Walk, Run, Fall�̏�Ԃ̂Ƃ��͐؂�ւ��\�̏�ԁB
		IsAction_canSwitching = vector<bool>(static_cast<int>(rollAction_Basic::_end), false);

		IsAction_canSwitching[static_cast<int>(rollAction_Basic::Idle)]
			= IsAction_canSwitching[static_cast<int>(rollAction_Basic::Walk)]
			= IsAction_canSwitching[static_cast<int>(rollAction_Basic::Run)]
			= IsAction_canSwitching[static_cast<int>(rollAction_Basic::Fall)]
			= IsAction_canSwitching[static_cast<int>(rollAction_Basic::Jump_Up)]
			= IsAction_canSwitching[static_cast<int>(rollAction_Basic::Jump_MidAir)]
			= IsAction_canSwitching[static_cast<int>(rollAction_Basic::Jump_Fall)]
			= true;
	};
	~AnimationSwitch() = default;

	//! �X�V���s���֐��B
	shared_ptr<Animation> update(
		shared_ptr<CollisionDetect> collision,
		shared_ptr<Animation> animation,
		Status playerStatus);

	//! ���݂ǂ̃A�N�V������Ԃ����擾����֐��B
	rollAction_Basic getNowAction() { return nowAction; }

};

