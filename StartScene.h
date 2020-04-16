
/*!
@file StartScene.h
@brief StartScene�N���X����`����Ă���w�b�_�t�@�C��
@date 2020/04/16/20:00
@author mimuro
*/

#pragma once
#include "AbstractScene.h"
#include <DxLib.h>

/*!
@class StartScene
@brief SystemLooper�N���X�Ő��������V�[���N���X�̈��AbstractScene���p������B�X�^�[�g��ʂ�S������B
@date 2020/04/16/20:00
@author mimuro
*/
class StartScene : public AbstractScene
{
public:
	//! �R���X�g���N�^�Ăяo������shared_ptr<ISceneChanger>�^�̃I�u�W�F�N�g���󂯎��A�e��AbstractScene�N���X�̃R���X�g���N�^�ɑ������B
	StartScene(shared_ptr<ISceneChanger> _changer) : AbstractScene(_changer) {};
	~StartScene() = default;

	//! ���j���[��ʂɕK�v�ȑO�������s���֐��B
	void update() override;

	//! ���j���[��ʂ̕`����s���֐��B
	void draw()  override;
};

