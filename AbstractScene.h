#pragma once
#include "ISceneChanger.h"
#include <memory>

using namespace std;

/*!
@brief �V�[�����Ǘ�����N���X�ASystemLooper�Ŏg�p
@date 2020/04/14/16:00
@author mimuro
*/
class AbstractScene
{
	shared_ptr<ISceneChanger> changer;
public:
	AbstractScene(
		shared_ptr<ISceneChanger> _changer
	) 
		: changer(_changer){};
	~AbstractScene() = default;
	virtual void draw() = 0;
	virtual void update() = 0;
};

