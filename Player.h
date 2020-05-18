
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
#include "AnimationSwitch.h"
#include "CollisionDetect.h"
#include "PlayerDirect.h"
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

	//! �v���C���[�I�u�W�F�N�g�̍��W�Ȃǂ̏����܂Ƃ߂�I�u�W�F�N�g�B
	Define::Status playerStatus;

	//! �X�e�[�W���ړ������鑬�x
	Dimention shiftingStage;

	//! �A�j���[�V�����̏������܂Ƃ߂čs���I�u�W�F�N�g�B
	std::shared_ptr<Animation> animation;

	//! �A�j���[�V��������Status�̍��W�̍X�V������I�u�W�F�N�g�B
	std::shared_ptr<AnimationMove> animationMove;

	//! �v���C���[�I�u�W�F�N�g�̓����蔻�菈�����܂Ƃ߂čs���I�u�W�F�N�g�B
	std::shared_ptr<CollisionDetect> collision;

	//! �A�N�V������Ԃ�؂�ւ��鏈�����܂Ƃ߂čs���I�u�W�F�N�g�B
	std::shared_ptr<AnimationSwitch> animationSwitch;

	//! �v���C���[�I�u�W�F�N�g���ǂ����̕����Ɍ��������肷��I�u�W�F�N�g�B
	std::shared_ptr<PlayerDirect> playerDirect;

public:

	Player(std::shared_ptr<Stage> _stage)
	{
		// �������̐ݒ�B
		playerStatus._x = Define::WIN_W / 2;
		playerStatus._y = Define::WIN_H / 2;

		playerStatus._x_speed = playerStatus._y_speed = 0;

		playerStatus.directRight = true;

		shiftingStage.x = shiftingStage.y = 0;

		animation = std::make_shared<Animation>(imagePath::getIns()->unityChan_Fall, playerStatus);

		animationMove = std::make_shared<AnimationMove>();

		collision = std::make_shared<CollisionDetect>(_stage, playerStatus);

		animationSwitch = std::make_shared<AnimationSwitch>();

		playerDirect = std::make_shared<PlayerDirect>();

	};

	~Player() = default;

	//! Player�I�u�W�F�N�g�̑O�����S�ʂ��s���֐��B
	void update(std::shared_ptr<Stage> _stage);

	//! Player�I�u�W�F�N�g�̕`�揈���S�ʂ��s���֐��B
	void draw();

	const Define::Status getStatus() { return playerStatus; }

	const Dimention getShiftingState() { return shiftingStage; }

};
