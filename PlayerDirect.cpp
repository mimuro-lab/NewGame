
/*!
@file PlayerDirect.cpp
@brief PlayerDirect�N���X���̃����o�ނ̒�`���s��CPP�t�@�C���B
@date 2020/05/04/17:47
@author mimuro
*/

#include "PlayerDirect.h"

/*!
@brief �A�N�V������Ԃ�run��walk�̎��̂ݕ����̕ϊ����󂯕t����悤�ɂ���B
@date 2020/05/04/17:47
@author mimuro
*/
bool PlayerDirect::updateDirect(Define::unityChan_Basic nowAction, bool nowDirectRight, Define::Status nowStatus)
{
	// ���̃A�N�V������Ԃ�walk��������R���g���[���̓��͏�ԂŌ�����ς���B
	if (nowAction == Define::unityChan_Basic::Walk ||
		nowAction == Define::unityChan_Basic::Run /*||
		nowAction == Define::unityChan_Basic::Jump_Up ||
		nowAction == Define::unityChan_Basic::Jump_MidAir ||
		nowAction == Define::unityChan_Basic::Jump_Fall ||
		nowAction == Define::unityChan_Basic::Fall*/
		) {
		if (Controller::getIns()->getOnRight())
			return true;
		if (Controller::getIns()->getOnLeft())
			return false;
	}

	if (nowAction == Define::unityChan_Basic::Jump_Up ||
		nowAction == Define::unityChan_Basic::Jump_MidAir ||
		nowAction == Define::unityChan_Basic::Jump_Fall ||
		nowAction == Define::unityChan_Basic::Fall) {
		if (nowStatus._x_speed > 0)
			return true;
		else if (nowStatus._x_speed < 0)
			return false;
		// x���x��0�̎��A�R���g���[���̓��͂Ŕ��f����B
		if (Controller::getIns()->getOnRight())
			return true;
		if (Controller::getIns()->getOnLeft())
			return false;
	}

	// ��L�̏�ԈȊO�̎��͌��݂̌������ێ�����B
	return nowDirectRight;

}