
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
#include "VirtualController.h"
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

	//! �A�N�V�������ɑ��̃A�N�V�����ɐ؂�ւ��\���ǂ����H�i�Y������unityChan_Basic�ɑΉ��j
	vector<bool> IsAction_canSwitching;

	//! �v���C���[�I�u�W�F�N�g�̌��݂̏�Ԃ��Ǘ��B
	unityChan_Basic nowAction;

	//// ���̃A�N�V���������݂̏����ɂ���đI�����Ă����B
	//! ���̃A�N�V�������i�[���Ă����ϐ��B
	unityChan_Basic nextAction;

	//! �v���C���[�I�u�W�F�N�g�̍��W�Ȃǂ̏����܂Ƃ߂�I�u�W�F�N�g�B
	Status playerStatus;

	//! ���A�N�V���������̃R���{�ɂ��邩�ǂ����B
	bool soardCombContinue = false;

	//! �A�N�V������Ԃ�؂�ւ��Ă��悢����Ԃ��B
	bool acceptSwitching(shared_ptr<Animation> animation, unityChan_Basic nowAction);

	//! �R���g���[���̓��͂Ȃǂɉ��������̃A�N�V�������擾����B
	unityChan_Basic getNextAction(
		shared_ptr<CollisionDetect> _collision, 
		shared_ptr<Animation> _animation, 
		Status playerStatus,
		unityChan_Basic nowAction
		, VirtualController controller);
	
	//! getNextAction�ɂ�蓾�����̃A�N�V������Ԃ�K������Ă悢���ǂ�����Ԃ��֐��B
	bool acceptNextAction(unityChan_Basic nowAction, unityChan_Basic nextAction, Status _playerStatus);

	//! animation�����t���b�V�����Ă��悢�����f����֐��B
	bool isRefresh(unityChan_Basic nowAction, shared_ptr<Animation> __animation);
	
	//! �A�j���[�V������؂�ւ���֐��B
	shared_ptr<Animation> switchingAnimation(unityChan_Basic next, Status _playerStatus);

	//! ���U���̃R���{������
	bool getSoardComb(unityChan_Basic nowAction, shared_ptr<Animation> __animation, bool nowCombContinue, VirtualController controller);

public:
	AnimationSwitch()
	{ 
		// nowAction�͍ŏ��AFall����n�߂�B
		nowAction = unityChan_Basic::Fall;
		
		// IsAction_canSwitchin�̏������B Idle, Walk, Run, Fall�̏�Ԃ̂Ƃ��͐؂�ւ��\�̏�ԁB
		IsAction_canSwitching = vector<bool>(static_cast<int>(unityChan_Basic::_end), false);

		IsAction_canSwitching[static_cast<int>(unityChan_Basic::Idle)]
			= IsAction_canSwitching[static_cast<int>(unityChan_Basic::Walk)]
			= IsAction_canSwitching[static_cast<int>(unityChan_Basic::Run)]
			= IsAction_canSwitching[static_cast<int>(unityChan_Basic::Fall)]
			= IsAction_canSwitching[static_cast<int>(unityChan_Basic::Jump_Up)]
			= IsAction_canSwitching[static_cast<int>(unityChan_Basic::Jump_MidAir)]
			= IsAction_canSwitching[static_cast<int>(unityChan_Basic::Jump_Fall)]
			= true;
	};
	~AnimationSwitch() = default;

	//! �X�V���s���֐��B
	shared_ptr<Animation> update(
		shared_ptr<CollisionDetect> collision,
		shared_ptr<Animation> animation,
		Status playerStatus,
		VirtualController controller);

	//! ���݂ǂ̃A�N�V������Ԃ����擾����֐��B
	unityChan_Basic getNowAction() { return nowAction; }

};

