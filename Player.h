
/*!
@file Player.h
@brief Player�N���X����`����Ă���w�b�_�t�@�C��
@date 2020/04/21/12:26
@author mimuro
*/

#pragma once
#include <DxLib.h>
#include "Task.h"
#include "Define.h"
#include "imagePath.h"
#include "Controller.h"
#include "Animation.h"
#include <memory>

/*!
@class Player
@brief Player�L�����̏����S�ʂ�S���N���X�B
@date 2020/04/21/12:28
@author mimuro
*/
class Player :
	public Task
{

	//! �������x
	char speed_walk = 2;
	//! ���鑬�x
	char speed_run = 4;

	//! �v���C���[�I�u�W�F�N�g�̍s���̕��ށB
	enum playerAction {
		Brake, Crouch, Damage, Idle, Jump_Fall, Jump_Landing, Jump_MidAir, Jump_Up, Run, Walk, _end
	};

	//! �v���C���[�I�u�W�F�N�g�̌��݂̏�Ԃ��Ǘ��B
	playerAction IsAction;

	//! �A�N�V�������ɑ��̃A�N�V�����ɐ؂�ւ��\���ǂ����H�i�Y������playerAction�ɑΉ��j
	std::vector<bool> IsAction_canSwitching;

	//! �v���C���[�I�u�W�F�N�g�̍��W�Ȃǂ̏����܂Ƃ߂�I�u�W�F�N�g�B
	Define::Status playerStatus;

	//! �A�j���[�V�����̏������܂Ƃ߂čs���I�u�W�F�N�g�B
	std::shared_ptr<Animation> animation = std::make_shared<Animation>(imagePath::getIns()->unityChan_Idle, playerStatus);

	//! �A�j���[�V������؂�ւ���֐��B
	std::shared_ptr<Animation> switchingAnimation(playerAction next);

	//! �R���g���[���̓��͂Ȃǂɉ��������̃A�N�V�������擾����B
	playerAction getNextAction();

	//! �v���C���[�I�u�W�F�N�g��Status�̍X�V���s���B
	Define::Status updateStatus(Define::Status _nowStatus);
public:

	Player() : 
		IsAction(Idle)
	{
		// �������̐ݒ�B
		/*
		playerStatus._x = Define::WIN_W / 2;
		playerStatus._y = Define::WIN_H / 2;
		*/
		playerStatus._x = 200;
		playerStatus._y = 100;
		playerStatus.directRight = true;

		// IsAction_canSwitchin�̏������B Idle, Walk, Run�̏�Ԃ̂Ƃ��͐؂�ւ��\�̏�ԁB
		IsAction_canSwitching = std::vector<bool>(_end, false);
		IsAction_canSwitching[Idle] = IsAction_canSwitching[Walk] = IsAction_canSwitching[Run] = true;

	};

	~Player() = default;

	//! Player�I�u�W�F�N�g�̑O�����S�ʂ��s���֐��B
	void update() override;

	//! Player�I�u�W�F�N�g�̕`�揈���S�ʂ��s���֐��B
	void draw() override;
};
