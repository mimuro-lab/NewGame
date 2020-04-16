#pragma once
#include "AbstractScene.h"
#include <DxLib.h>

class ConfigScene : public AbstractScene
{
public:
	//! �R���X�g���N�^�Ăяo������shared_ptr<ISceneChanger>�^�̃I�u�W�F�N�g���󂯎��A�e��AbstractScene�N���X�̃R���X�g���N�^�ɑ������B
	ConfigScene(shared_ptr<ISceneChanger> _changer) : AbstractScene(_changer) {};
	~ConfigScene() = default;

	//! ���j���[��ʂɕK�v�ȑO�������s���֐��B
	void update() override;

	//! ���j���[��ʂ̕`����s���֐��B
	void draw()  override;
};

