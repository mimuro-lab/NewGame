
/*!
@file Menu.h
@brief Menu�N���X����`����Ă���w�b�_�t�@�C��
@date 2020/04/16/03:02
@author mimuro
*/

#pragma once
#include "AbstractScene.h"
#include <DxLib.h>
#include <memory>

using namespace std;

/*!
@class Menu
@brief SystemLooper�N���X�Ő��������V�[���N���X�̈��AbstractScene���p������B���j���[��ʂ�S������B
@date 2020/04/16/03:02
@author mimuro
*/
class Menu : public AbstractScene
{
public:
	//! �R���X�g���N�^�Ăяo������shared_ptr<ISceneChanger>�^�̃I�u�W�F�N�g���󂯎��A�e��AbstractScene�N���X�̃R���X�g���N�^�ɑ������B
	Menu(shared_ptr<ISceneChanger> _changer)  : AbstractScene(_changer) {};
	~Menu() = default;

	//! ���j���[��ʂɕK�v�ȑO�������s���֐��B
	void update() override;

	//! ���j���[��ʂ̕`����s���֐��B
	void draw()  override;
};

