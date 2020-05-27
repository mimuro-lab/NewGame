#pragma once
#include "Stage.h"
#include "Define.h"
#include <memory>

class AbsDamageObj
{
protected:
	bool isLive = true;
public:
	AbsDamageObj() = default;
	~AbsDamageObj() = default;

	//! Player�I�u�W�F�N�g�̑O�����S�ʂ��s���֐��B
	virtual void update(std::shared_ptr<Stage> _stage, Dimention shiftingStageVel, Status playerStatus) = 0;

	//! Player�I�u�W�F�N�g�̕`�揈���S�ʂ��s���֐��B
	virtual void draw() = 0;

	const bool getIsLive() { return isLive; }
};

