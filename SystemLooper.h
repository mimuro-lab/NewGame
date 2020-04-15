#pragma once
#include <DxLib.h>
#include "ISceneChanger.h"
#include "AbstractScene.h"
#include <stack>
#include <memory>

using namespace std;

/*!
@brief ���[�v���鏈���̒��S��S���N���X
@date 2020/04/15/15:12
@author mimuro
*/
class SystemLooper : private ISceneChanger
{
	stack <shared_ptr<AbstractScene>> scene;
public:
	SystemLooper() = default;
	~SystemLooper() = default;
	bool Error() const;
	bool scrProcess() const;

	void changeScene(eScene NextScene) const override;
};

