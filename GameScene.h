
/*!
@file GameScene.h
@brief GameScene�N���X����`����Ă���w�b�_�t�@�C��
@date 2020/04/16/19:55
@author mimuro
*/

#pragma once
#include <DxLib.h>
#include <memory>
#include <vector>
#include "AbstractScene.h"
#include "Controller.h"
#include "SelectWindow.h"
#include "imagePath.h"
#include "Player.h"
#include "Stage.h"
#include "DamageObj.h"

using namespace std;

/*!
@class GameScene
@brief SystemLooper�N���X�Ő��������V�[���N���X�̈��AbstractScene���p������B�Q�[����ʂ�S������B
@date 2020/04/16/19:56
@author mimuro
*/
class GameScene :
	public AbstractScene,
	private SelectWindow
{
	//! �w�i��Stage�̏������s���I�u�W�F�N�g
	shared_ptr<Stage> stage;

	//! Player�̏������ɂȂ��I�u�W�F�N�g
	shared_ptr<Player> player;

	//! ��ʏ�̃_���[�W�v�f
	vector<shared_ptr<DamageObj>> damageObjs;

public:
	//! �R���X�g���N�^�Ăяo������shared_ptr<ISceneChanger>�^�̃I�u�W�F�N�g���󂯎��A�e��AbstractScene�N���X�̃R���X�g���N�^�ɑ������B
	GameScene(shared_ptr<ISceneChanger> _changer) : 
		AbstractScene(_changer), 
		SelectWindow(_changer), 
		stage(make_shared<Stage>(Define::blockWidth, Define::blockHeight)), 
		player(make_shared<Player>(stage)) 
	{};
	~GameScene() = default;

	//! �Q�[����ʂɕK�v�ȑO�������s���֐��B
	void update() override;

	//! �Q�[����ʂ̕`����s���֐��B
	void draw() override;
};

