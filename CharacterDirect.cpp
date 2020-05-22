
/*!
@file CharacterDirect.cpp
@brief CharacterDirect�N���X���̃����o�ނ̒�`���s��CPP�t�@�C���B
@date 2020/05/04/17:47
@author mimuro
*/

#include "CharacterDirect.h"

/*!
@brief �A�N�V������Ԃ�run��walk�̎��̂ݕ����̕ϊ����󂯕t����悤�ɂ���B
@date 2020/05/04/17:47
@author mimuro
*/
bool CharacterDirect::updateDirect(Define::unityChan_Basic nowAction, bool nowDirectRight, Define::Status nowStatus, VirtualController controller)
{
	// ���̃A�N�V������Ԃ�walk��������R���g���[���̓��͏�ԂŌ�����ς���B
	if (nowAction == Define::unityChan_Basic::Walk ||
		nowAction == Define::unityChan_Basic::Run /*||
		nowAction == Define::unityChan_Basic::Jump_Up ||
		nowAction == Define::unityChan_Basic::Jump_MidAir ||
		nowAction == Define::unityChan_Basic::Jump_Fall ||
		nowAction == Define::unityChan_Basic::Fall*/
		) {
		if (controller.on_right)
			return true;
		if (controller.on_left)
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
		if (controller.on_right)
			return true;
		if (controller.on_left)
			return false;
	}

	// ��L�̏�ԈȊO�̎��͌��݂̌������ێ�����B
	return nowDirectRight;

}