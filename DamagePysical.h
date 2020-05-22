#pragma once
#include "Define.h"

using namespace Define;

class DamagePysical
{

	unsigned char gravity = Accel_gravity;

	Dimention velocity;

	Dimention accel;

	//! affectGravity�i�Ώۂ̉����x�j�ɑ΂��A�d�͂�������B
	Dimention affectGravity(Dimention affectedAcc) {
		Dimention nextAcc = affectedAcc;
		nextAcc.y += gravity;
		return nextAcc;
	}

	//! �����x���瑬�x���v�Z����B
	Dimention calcVelocityFromAccel(Dimention affectedVel, Dimention affectAcc);

	//! ���x����ʒu���v�Z����B
	Dimention calcPointFromVelocity(Dimention affectPoint, Dimention affectVel);

public:
	DamagePysical() {
		velocity.x = velocity.y = 0;
		accel.x = accel.y = 0;
	}
	~DamagePysical() = default;

	Dimention update(Dimention nowPoint);

};

