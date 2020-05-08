
/*!
@file Pysical.h
@brief PredictPoint�N���X����`����Ă���w�b�_�t�@�C���B
@date 2020/05/04/19:09
@author mimuro
*/

#pragma once
#include "Define.h"
#include "CollisionDetect.h"

/*!
@class Pysical
@brief �������Z�ɒu���đ��x�̉��Z��S���N���X�B
@date 2020/05/04/19:12
@author mimuro
*/
using namespace Define;

class Pysical {

	//! ���݂̑��x���Ǘ�����ϐ��B
	Dimention now_vel;

	//! ���݂̉����x���Ǘ�����ϐ��B
	Dimention now_acc;

	//! Action���̎��ԁAAction���؂�ւ��ƂO�Ƀ��Z�b�g�����B
	unsigned short int time = 0;

	// moveN�R�}�Ɉ������x��������B
	unsigned char addAccN = 2;
	unsigned char addAccCounter = 0;

	//! �d�͂̒l
	unsigned char acc_gravity = 1;

	//! ���C�͂̒l
	unsigned char acc_friction = 1;

	//! �u���b�N�Ƃ̔����W��(���鐔�A�傫���Ƒ��x�͏������Ȃ�)
	float coef_block = 0.3;

	// Action���Ƃ̉����x�̑傫���Ƒ��x�̌��E�l
	unsigned char acc_brake = 0;

	unsigned char acc_walk = 1;
	unsigned char limVel_walk = 3;

	unsigned char acc_run = 1;
	unsigned char limVel_run = 7;

	unsigned char initVel_jumpUp = 12;
	unsigned char initVel_jumpMidAir = 3;

	//! �����x���i�[����ϐ��B
	std::vector<Dimention> _isInitVelocity;

	//! ���̃A�N�V������Ԃ̎��ɏd�͂�L���ɂ��邩�ǂ������Ǘ�����ϐ��B
	std::vector<bool> _validGravityAction;

	//! ���̃A�N�V������Ԃ̎��ɖ��C�͂�L���ɂ��邩�ǂ������Ǘ�����ϐ��B
	std::vector<bool> _validFrictionAction;

	//! �Ώۂ̑��x�ɑ΂��A�����x������ɗ^����֐��B
	Dimention affectInitVelocity(Dimention affectedVel, rollAction_Basic nowAction, unsigned short nowTime);

	//! affectGravity�i�Ώۂ̉����x�j�ɑ΂��A�d�͂�������B
	Dimention affectGravity(Dimention affectedAcc, rollAction_Basic nowAction);

	//! affectGravity�i�Ώۂ̉����x�j�ɑ΂��A����ɒn�ʂƂ̖��C��������B
	Dimention affectFriction(Dimention affectedAcc, rollAction_Basic nowAction, bool isDireRight);

	//! �A�N�V������ԂƂ��̕�����������x�𓾂�B
	Dimention getForceFromAction(rollAction_Basic nowAction, bool isDireRight);

	//! �A�N�V������ԂƂ��̕������瑬�x�̌��E�l�𓾂�B
	Dimention getLimitVelFromAction(rollAction_Basic nowAction, bool isDireRight);
	
	//! �����x���瑬�x���v�Z����B
	Dimention calcVelocityFromAccel(Dimention affectedVel, Dimention affectAcc, rollAction_Basic nowAction, bool isDireRight);

	//! �����Ă�������Ƒ��x�������Ⴄ�Ƃ��͑��x��0�ɂ���B�i���������̂݁j
	Dimention matchingVelAndDireHorizon(Dimention affectedVel, bool isDireRight);

	//! ���x�𓖂��蔻��ɂ�胊�Z�b�g����B
	Dimention resetByCollision(Dimention resetedVector, std::shared_ptr<CollisionDetect> _collision);
		
	rollAction_Basic preIsAction = rollAction_Basic::Idle;
	//! Action���؂�ւ�����u�Ԃ��擾����֐�
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
		_isInitVelocity[static_cast<int>(Define::rollAction_Basic::Jump_Up)].y = - initVel_jumpUp;
		_isInitVelocity[static_cast<int>(Define::rollAction_Basic::Jump_MidAir)].y = -initVel_jumpMidAir;

		_validGravityAction = std::vector<bool>(static_cast<int>(Define::rollAction_Basic::_end), false);
		_validGravityAction[static_cast<int>(Define::rollAction_Basic::Fall)]
			= _validGravityAction[static_cast<int>(Define::rollAction_Basic::Jump_Up)]
			= _validGravityAction[static_cast<int>(Define::rollAction_Basic::Jump_MidAir)]
			= _validGravityAction[static_cast<int>(Define::rollAction_Basic::Brake)]
			= _validGravityAction[static_cast<int>(Define::rollAction_Basic::Crouch)]
			= true;

		_validFrictionAction = std::vector<bool>(static_cast<int>(Define::rollAction_Basic::_end), false);
		_validFrictionAction[static_cast<int>(Define::rollAction_Basic::Idle)]
			= _validFrictionAction[static_cast<int>(Define::rollAction_Basic::Brake)]
			= _validFrictionAction[static_cast<int>(Define::rollAction_Basic::Crouch)]
			= _validFrictionAction[static_cast<int>(Define::rollAction_Basic::Jump_Landing)]
			= true;
	};
	~Pysical() = default;


	//! �A�N�V������ԂƂ��̕����ɂ�葬�x�Ɖ����x���X�V���A���x��Ԃ��B
	Dimention update(rollAction_Basic nowAction, bool isDireRight);

	//! ���W���Z�b�g������A�K�؂ɑ��x�����Z�b�g����B
	Dimention resetVelocity(Dimention resetedVector, std::shared_ptr<CollisionDetect> _collision);
};