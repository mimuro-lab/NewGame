
/*!
@file Pysical.cpp
@brief Pysical�N���X���̃����o�ނ̒�`���s��CPP�t�@�C���B
@date 2020/05/04/19:17
@author mimuro
*/

#include "Pysical.h"

/*!
@brief �����x��L���ɂ���BnowTime��0�̎��̂ݑ��x�ɑ΂��A�����x��^����B�����̂͑��x���O��B
@date 2020/05/04/19:19
@author mimuro
*/
Dimention Pysical::affectInitVelocity(Dimention affectedVel, rollAction_Basic nowAction, unsigned char nowTime)
{
	Dimention returnVel = affectedVel;

	if (nowTime == 0) {
		returnVel.x += _isInitVelocity[static_cast<int>(nowAction)].x;
		returnVel.y += _isInitVelocity[static_cast<int>(nowAction)].y;
	}

	return returnVel;
}

/*!
@brief �d�͂�L���ɂ���֐��B�����͉̂����x���O��B
@date 2020/05/04/19:19
@author mimuro
*/
Dimention Pysical::affectGravity(Dimention affectedAcc, rollAction_Basic nowAction)
{
	Dimention returnAcc = affectedAcc;

	if(_validGravityAction[static_cast<int>(nowAction)])
		returnAcc.y += acc_gravity;

	return returnAcc;

}

/*!
@brief ���C�͂�L���ɂ���֐��B�����͉̂����x���O��B
@date 2020/05/04/19:19
@author mimuro
*/
Dimention Pysical::affectFriction(Dimention affectedAcc, rollAction_Basic nowAction, bool isDireRight)
{
	Dimention returnAcc = affectedAcc;

	if (_validFrictionAction[static_cast<int>(nowAction)]) {
		if (isDireRight)
			returnAcc.x -= acc_friction;
		if (!isDireRight)
			returnAcc.x += acc_friction;
	}

	return returnAcc;
}

/*!
@brief Action��Ԃ���A���̎��̉����x�𓾂�B
@date 2020/05/04/19:19
@author mimuro
*/
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

/*!
@brief Action��Ԃ���A���̎��̑��x�̌��E�l�𓾂�B�������l�����Ă���A�����̂͑��x���O��B
@date 2020/05/04/19:26
@author mimuro
*/
Dimention Pysical::getLimitVelFromAction(rollAction_Basic nowAction, bool isDireRight)
{
	Dimention returnVelocity;

	returnVelocity.x = returnVelocity.y = 128;

	switch (nowAction) {
	case rollAction_Basic::Walk:
		if(isDireRight)
			returnVelocity.x = limVel_walk;
		else
			returnVelocity.x = -limVel_walk;
		break;
	case rollAction_Basic::Run:
		if (isDireRight)
			returnVelocity.x = limVel_run;
		else
			returnVelocity.x = -limVel_run;
		break;
	}

	return returnVelocity;
}

/*!
@brief ���̎��̉����x����A���̑��x���v�Z����B�Ԃ��̂͑��x�B
@date 2020/05/04/19:26
@author mimuro
*/
Dimention Pysical::calcVelocityFromAccel(Dimention affectedVel, Dimention affectAcc, rollAction_Basic nowAction, bool isDireRight)
{
	Dimention returnVelocity = affectedVel;
	
	int limitX = std::abs(getLimitVelFromAction(nowAction, isDireRight).x);
	int nextVelAbs = std::abs(returnVelocity.x + affectAcc.x);

	// �X�V��̑��x�����E�l�𒴂��Ȃ��悤�ł���Α��x�ɉ����x�𑫂�
	if (nextVelAbs <= limitX) {
		returnVelocity.x += affectAcc.x;
	}
	// ������悤�ł���Ό��E�l�ɐݒ肷��B(�����ɂ����)
	else
		returnVelocity.x = getLimitVelFromAction(nowAction, isDireRight).x;

	returnVelocity.y += affectAcc.y;

	return returnVelocity;
}

/*!
@brief ���x�ƌ����������قȂ�Ƃ��i�Ⴆ��Brake�j�ɁA�����x���t�����ɂ����肷���Ȃ��悤�ɐ��䂷��֐��B�Ԃ��̂͑��x�B
@date 2020/05/04/19:26
@author mimuro
*/
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

/*!
@brief ���݂̃A�N�V������Ԃ��瑬�x���v�Z���A�Ԃ��B
@date 2020/05/04/19:26
@author mimuro
*/
Dimention Pysical::update(rollAction_Basic nowAction, bool isDireRight)
{

	// Action���؂�ւ�����玞�Ԃ��O�ɂ���B
	if (isSwitching(nowAction))
		time = 0;

	// �����x��L���ɂ���B
	now_vel = affectInitVelocity(now_vel, nowAction, time);

	// �����x���v�Z����B
	if (addAccCounter == 0) {
		now_acc = getForceFromAction(nowAction, isDireRight);
		now_acc = affectGravity(now_acc, nowAction);
		now_acc = affectFriction(now_acc, nowAction, isDireRight);
	}
	else {
		now_acc.x = now_acc.y = 0;
	}
	addAccCounter++;
	addAccCounter %= addAccN;

	// �����x���瑬�x���X�V����B
	now_vel = calcVelocityFromAccel(now_vel, now_acc, nowAction, isDireRight);

	// �����Ă�������Ɛ��������̑��x�����̒��a���Ƃ�B
	now_vel = matchingVelAndDireHorizon(now_vel, isDireRight);

	time++;

	return now_vel;
}

/*!
@brief ��ǂɂԂ��������ɑ��x�����Z�b�g����֐��B
@date 2020/05/04/19:26
@author mimuro
*/
Dimention Pysical::resetByCollision(Dimention resetedVector, std::shared_ptr<CollisionDetect> _collision)
{

	Dimention retVec = resetedVector;

	// ���x���O�̎��͂�����Ȃ��B

	/// y���x�̏���
	// ���x���������A���A�������Փ˂��Ă���Ȃ�y���x�����Z�b�g
	if (resetedVector.y > 0 && _collision->getCollisionedSide().bottom)
		retVec.y = 0;

	// ���x��������A���A�㑤���Փ˂��Ă���Ȃ�y���x�����Z�b�g(���x��0���܂߂�̂́A�W�����v�������Ƀ��Z�b�g�����)
	if (resetedVector.y <= 0 && _collision->getCollisionedSide().head)
		retVec.y = 0;

	/// x���x�̏���
	// ���x���E�����A���A�E�����Փ˂��Ă���Ȃ�x���x�����Z�b�g
	if (resetedVector.x > 0 && _collision->getCollisionedSide().right)
		retVec.x = 0;

	// ���x���������A���A�������Փ˂��Ă���Ȃ�x���x�����Z�b�g
	if (resetedVector.x < 0 && _collision->getCollisionedSide().left)
		retVec.x = 0;

	return retVec;
}

/*!
@brief ���x��K�؂ȃ��Z�b�g��������B
@date 2020/05/04/19:34
@author mimuro
*/
Dimention Pysical::resetVelocity(Dimention resetedVector, std::shared_ptr<CollisionDetect> _collision)
{
	Dimention retVec = resetedVector;

	retVec = resetByCollision(retVec, _collision);

	now_vel = retVec;

	return retVec;

}