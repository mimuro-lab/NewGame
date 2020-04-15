#pragma once
#include <DxLib.h>
#include "ISceneChanger.h"
#include "AbstractScene.h"
#include "Menu.h"
#include <stack>
#include <memory>

using namespace std;

/*!
@brief ���[�v���鏈���̒��S��S���N���X
@date 2020/04/15/15:12
@author mimuro
*/
class SystemLooper : public ISceneChanger,
	public enable_shared_from_this<SystemLooper>
{
	stack <shared_ptr<AbstractScene>> scene;
public:
	SystemLooper();
	~SystemLooper() = default;

	bool Initialize() ;

	bool Error() const;
	bool scrProcess() const;

	void loop() const;

	void changeScene(eScene NextScene) const override;
};

