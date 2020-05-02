#include "Pysical.h"

Dimention Pysical::affectInitVelocity(Dimention affectedVel, rollAction_Basic nowAction, unsigned char nowTime)
{
	Dimention returnVel = affectedVel;

	if (nowTime == 0) {
		returnVel.x += _isInitVelocity[static_cast<int>(nowAction)].x;
		returnVel.y += _isInitVelocity[static_cast<int>(nowAction)].y;
	}

	return returnVel;
}

Dimention Pysical::affectGravity(Dimention affectedAcc, rollAction_Basic nowAction)
{
	Dimention returnAcc = affectedAcc;

	if(_validGravityAction[static_cast<int>(nowAction)])
		returnAcc.y += acc_gravity;

	return returnAcc;

}

Dimention Pysical::affectBraking(Dimention affectedAcc, rollAction_Basic nowAction)
{
	Dimention returnAcc = affectedAcc;

	if (_validBrakingAction[static_cast<int>(nowAction)])
		returnAcc.y += acc_brake;

	return returnAcc;
}

Dimention Pysical::getForceFromAction(rollAction_Basic nowAction, bool isDireRight)
{
	Dimention returnForce;

	returnForce.x = returnForce.y = 0;

	switch (nowAction) {
	case rollAction_Basic::Brake:
		if (isDireRight)
			returnForce.x = -acc_brake;
		else
			returnForce.x = acc_brake;
		break;
	case rollAction_Basic::Idle:
		if (isDireRight)
			returnForce.x = -acc_brake;
		else
			returnForce.x = acc_brake;
		break;
	case rollAction_Basic::Walk:
		if (isDireRight)
			returnForce.x = acc_walk;
		else
			returnForce.x = -acc_walk;
		break;
	case rollAction_Basic::Run:
		if (isDireRight)
			returnForce.x = acc_run;
		else
			returnForce.x = -acc_run;
		break;
	}

	return returnForce;
}

Dimention Pysical::calcVelocityFromAccel(Dimention affectedVel, Dimention affectAcc)
{
	Dimention returnVelocity = affectedVel;

	returnVelocity.x += affectAcc.x;
	returnVelocity.y += affectAcc.y;

	return returnVelocity;
}

Dimention Pysical::matchingVelAndDireHorizon(Dimention affectedVel, bool isDireRight)
{
	Dimention returnVel = affectedVel;

	// �E�������āA���x���O��菬�����Ȃ瑬�x���O�ɂ���B
	if (isDireRight && returnVel.x < 0) 
		returnVel.x = 0;
	// ���������āA���x���O���傫���Ȃ瑬�x���O�ɂ���B
	if (!isDireRight && returnVel.x > 0)
		returnVel.x = 0;

	return returnVel;
}

Dimention Pysical::update(rollAction_Basic nowAction, bool isDireRight)
{

	// Action���؂�ւ�����玞�Ԃ��O�ɂ���B
	if (isSwitching(nowAction))
		time = 0;

	// �����x��L���ɂ���B
	now_vel = affectInitVelocity(now_vel, nowAction, time);

	// �����x���v�Z����B
	now_acc = getForceFromAction(nowAction, isDireRight);
	now_acc = affectGravity(now_acc, nowAction);
	now_acc = affectBraking(now_acc, nowAction);

	// �����x���瑬�x���X�V����B
	now_vel = calcVelocityFromAccel(now_vel, now_acc);

	// �����Ă�������Ɛ��������̑��x�����̒��a���Ƃ�B
	now_vel = matchingVelAndDireHorizon(now_vel, isDireRight);

	time++;

	return now_vel;
}