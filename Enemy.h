#pragma once

#include <DxLib.h>
#include "Define.h"
#include "ImagePath_Unitychan.h"
#include "Controller.h"
#include "VirtualController.h"
#include "Animation.h"
#include "AnimationMove.h"
#include "AnimationSwitch.h"
#include "CollisionDetect.h"
#include "CharacterDirect.h"
#include "AbsDamageObj.h"
#include "Stage.h"
#include <memory>
#include <vector>

using namespace Define;

class Enemy
{

	//! �R���g���[��
	VirtualController controller;

	//! �v���C���[�I�u�W�F�N�g�̍��W�Ȃǂ̏����܂Ƃ߂�I�u�W�F�N�g�B
	Define::Status enemyStatus;

	//! �A�j���[�V�����̏������܂Ƃ߂čs���I�u�W�F�N�g�B
	std::shared_ptr<Animation> animation;

	//! �A�j���[�V��������Status�̍��W�̍X�V������I�u�W�F�N�g�B
	std::shared_ptr<AnimationMove> animationMove;

	//! �v���C���[�I�u�W�F�N�g�̓����蔻�菈�����܂Ƃ߂čs���I�u�W�F�N�g�B
	std::shared_ptr<CollisionDetect> collision;

	//! �A�N�V������Ԃ�؂�ւ��鏈�����܂Ƃ߂čs���I�u�W�F�N�g�B
	std::shared_ptr<AnimationSwitch> animationSwitch;

	//! �v���C���[�I�u�W�F�N�g���ǂ����̕����Ɍ��������肷��I�u�W�F�N�g�B
	std::shared_ptr<CharacterDirect> enemyDirect;

	bool isAlive = true;

public:
	Enemy(std::shared_ptr<Stage> _stage, int init_x, int init_y)
	{

		// �������̐ݒ�B
		enemyStatus._x = init_x;
		enemyStatus._y = init_y;

		enemyStatus._x_speed = enemyStatus._y_speed = 0;

		enemyStatus.directRight = true;


		animation = std::make_shared<Animation>(ImagePath_Unitychan::getIns()->unityChan_Fall, enemyStatus);

		animationMove = std::make_shared<AnimationMove>();

		collision = std::make_shared<CollisionDetect>(_stage, enemyStatus, 10, 10, 10, 10, 15, 30, 10, 10);

		animationSwitch = std::make_shared<AnimationSwitch>();

		enemyDirect = std::make_shared<CharacterDirect>();

	};

	//! Player�I�u�W�F�N�g�̑O�����S�ʂ��s���֐��B
	void update(std::shared_ptr<Stage> _stage, Dimention shiftingStage, std::vector<std::shared_ptr<AbsDamageObj>> _damages);

	//! Player�I�u�W�F�N�g�̕`�揈���S�ʂ��s���֐��B
	void draw();

	const bool getIsAlive() { return isAlive; }

};

