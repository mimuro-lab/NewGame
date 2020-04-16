#pragma once
#include "AbstractScene.h"
#include <DxLib.h>
class StartScene : public AbstractScene
{
public:
	StartScene(shared_ptr<ISceneChanger> _changer) : AbstractScene(_changer) {};
	~StartScene() = default;

	//! ���j���[��ʂɕK�v�ȑO�������s���֐��B
	void update() override;

	//! ���j���[��ʂ̕`����s���֐��B
	void draw()  override;
};

