#pragma once
#include "Pysical.h"
class PysicalBullet :
	public Pysical
{
	int initVelX;
	int initVelY;
	bool _isDireRight;

	// �d�͂�N�R�}�Ɉ��L��
	unsigned char validGravityN = 6;
	unsigned char validGravityCounter = 0;


	Dimention affectInitVelocity(Dimention affectedVel, characterAction nowAction, unsigned short nowTime, shared_ptr<CollisionDetect> collision, bool isDireRight);

	//! affectGravity�i�Ώۂ̉����x�j�ɑ΂��A�d�͂�������B
	Dimention affectGravity(Dimention affectedAcc, characterAction nowAction) override;

public:
	PysicalBullet(int _initVelX, int _initVelY, bool __isDireRight) {
		initVelX = _initVelX;
		initVelY = _initVelY;
		_isDireRight = __isDireRight;
	}
	~PysicalBullet() = default;

	//! �A�N�V������ԂƂ��̕����ɂ�葬�x�Ɖ����x���X�V���A���x��Ԃ��B
	Dimention update(characterAction nowAction, bool isDireRight, shared_ptr<CollisionDetect> _collision, VirtualController controller);

};

