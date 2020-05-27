#include "PysicalBullet.h"

Dimention PysicalBullet::affectInitVelocity(Dimention affectedVel, characterAction nowAction, unsigned short nowTime, shared_ptr<CollisionDetect> collision, bool isDireRight)
{
	Dimention returnVel = affectedVel;

	if (nowTime == 0 && !collision->getCollisionedSide().bottom) {
		if (isDireRight)
			returnVel.x += std::abs(initVelX);
		else {
			returnVel.x -= std::abs(initVelX + limVel_walk)				;
		}
		returnVel.y += initVelY;
	}

	return returnVel;
}

/*!
@brief �d�͂�L���ɂ���֐��B�����͉̂����x���O��B
@date 2020/05/04/19:19
@author mimuro
*/
Dimention PysicalBullet::affectGravity(Dimention affectedAcc, characterAction nowAction)
{
	Dimention returnAcc = affectedAcc;

	if (_validGravityAction[static_cast<int>(nowAction)]) {
		validGravityCounter++;
		validGravityCounter %= validGravityN;
		if(validGravityCounter==0)
			returnAcc.y += acc_gravity;
	}

	return returnAcc;

}



/*!
@brief ���݂̃A�N�V������Ԃ��瑬�x���v�Z���A�Ԃ��B
@date 2020/05/04/19:26
@author mimuro
*/
Dimention PysicalBullet::update(characterAction nowAction, bool isDireRight, shared_ptr<CollisionDetect> collision, VirtualController controller)
{

	// Action���؂�ւ�����玞�Ԃ��O�ɂ���B
	if (isSwitching(nowAction))
		time = 0;

	// �����x��L���ɂ���B
	now_vel = affectInitVelocity(now_vel, nowAction, time, collision, _isDireRight);

	// �����x���v�Z����B
	if (addAccCounter == 0) {
		now_acc = getForceFromAction(nowAction, isDireRight, controller);
		now_acc = affectGravity(now_acc, nowAction);
		now_acc = affectFriction(now_acc, nowAction, isDireRight);
	}
	else {
		now_acc.x = now_acc.y = 0;
	}
	addAccCounter++;
	addAccCounter %= addAccN;

	// �����x���瑬�x���X�V����B
	now_vel = calcVelocityFromAccel(now_vel, now_acc, nowAction, isDireRight, controller);

	// �����Ă�������Ɛ��������̑��x�����̒��a���Ƃ�B
	now_vel = matchingVelAndDireHorizon(now_vel, nowAction, isDireRight);

	time++;
	//DrawFormatString(100, 70, GetColor(255, 255, 255), "now acc x:%d, y:%d", now_acc.x, now_acc.y);
	return now_vel;
}
