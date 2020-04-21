
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
	//! �v���C���[�I�u�W�F�N�g�̍��W�Ȃǂ̏����܂Ƃ߂�I�u�W�F�N�g�B
	Define::Status playerStatus;

	//! �A�j���[�V�����̏������܂Ƃ߂čs���I�u�W�F�N�g�B
	std::shared_ptr<Animation> animation = std::make_shared<Animation>(imagePath::getIns()->unityChan_Idle, 100,100);
public:
	Player();
	~Player() = default;

	//! Player�I�u�W�F�N�g�̑O�����S�ʂ��s���֐��B
	void update() override;

	//! Player�I�u�W�F�N�g�̕`�揈���S�ʂ��s���֐��B
	void draw() override;
};
