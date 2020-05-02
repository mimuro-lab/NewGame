#pragma once
#include "Define.h"
#include "CollisionDetect.h"

using namespace Define;

class Pysical {

	Dimention now_vel;
	Dimention now_acc;

	// Action���̎��ԁAAction���؂�ւ��ƂO�Ƀ��Z�b�g�����B
	unsigned short int time = 0;

	unsigned char acc_gravity = 1;

	unsigned char acc_brake = 1;

	unsigned char acc_walk = 2;

	unsigned char acc_run = 3;

	std::vector<Dimention> _isInitVelocity;
	std::vector<bool> _validGravityAction;
	std::vector<bool> _validBrakingAction;

	// �Ώۂ̑��x�ɑ΂��A�����x������ɗ^����B
	Dimention affectInitVelocity(Dimention affectedVel, rollAction_Basic nowAction, unsigned char nowTime);

	// affectGravity�i�Ώۂ̉����x�j�ɑ΂��A�d�͂�������B
	Dimention affectGravity(Dimention affectedAcc, rollAction_Basic nowAction);

	// affectGravity�i�Ώۂ̉����x�j�ɑ΂��A����ɒn�ʂƂ̖��C��������B
	Dimention affectBraking(Dimention affectedAcc, rollAction_Basic nowAction);

	// �A�N�V������ԂƂ��̕�����������x�𓾂�B
	Dimention getForceFromAction(rollAction_Basic nowAction, bool isDireRight);

	// �����x���瑬�x���v�Z����B
	Dimention calcVelocityFromAccel(Dimention affectedVel, Dimention affectAcc);

	// �����Ă�������Ƒ��x�������Ⴄ�Ƃ��͑��x��0�ɂ���B�i���������̂݁j
	Dimention matchingVelAndDireHorizon(Dimention affectedVel, bool isDireRight);

	// Action���؂�ւ�����u�Ԃ��擾����֐�
	rollAction_Basic preIsAction = rollAction_Basic::Idle;
	bool isSwitching(Define::rollAction_Basic nowAction) {
		bool ret = false;
		if (nowAction != preIsAction)	ret = true;
		else							ret = false;
		preIsAction = nowAction;
		return ret;
	}

public:

	Pysical()
	{
		now_vel.x = now_vel.y = 0;
		now_acc.x = now_acc.y = 0;

		Dimention initVel;
		initVel.x = initVel.y = 0;
		_isInitVelocity = std::vector<Dimention>(static_cast<int>(Define::rollAction_Basic::_end), initVel);
		_isInitVelocity[static_cast<int>(Define::rollAction_Basic::Jump_Up)].y = - 10;
		_isInitVelocity[static_cast<int>(Define::rollAction_Basic::Jump_MidAir)].y = -5;

		_validGravityAction = std::vector<bool>(static_cast<int>(Define::rollAction_Basic::_end), false);
		_validGravityAction[static_cast<int>(Define::rollAction_Basic::Fall)]
			= _validGravityAction[static_cast<int>(Define::rollAction_Basic::Jump_Up)]
			= _validGravityAction[static_cast<int>(Define::rollAction_Basic::Jump_MidAir)]
			= true;

		_validBrakingAction = std::vector<bool>(static_cast<int>(Define::rollAction_Basic::_end), false);
		_validBrakingAction[static_cast<int>(Define::rollAction_Basic::Idle)]
			= true;
	};
	~Pysical() = default;


	// �A�N�V������ԂƂ��̕����ɂ�葬�x�Ɖ����x���X�V���A���x��Ԃ��B
	Dimention update(rollAction_Basic nowAction, bool isDireRight);

};