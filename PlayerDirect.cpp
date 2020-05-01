#include "PlayerDirect.h"

bool PlayerDirect::updateDirect(Define::rollAction_Basic nowAction, bool nowDirectRight)
{
	/*
	// ���̃A�N�V������Ԃ��u���[�L�������������ς��Ȃ��B
	if (nowAction == Define::rollAction_Basic::Brake)
		return nowDirectRight;

	// ���̃A�N�V������Ԃ��W�����v���������������ς��Ȃ��B
	if (nowAction == Define::rollAction_Basic::Jump_Up ||
		nowAction == Define::rollAction_Basic::Jump_MidAir ||
		nowAction == Define::rollAction_Basic::Jump_Fall ||
		nowAction == Define::rollAction_Basic::Jump_Landing)
		return nowDirectRight;

	// ���̃A�N�V������Ԃ��u���[�L�������������ς��Ȃ��B
	if (nowAction == Define::rollAction_Basic::Brake)
		return nowDirectRight;

	// ���̃A�N�V������Ԃ��A�C�h�����O�������������ς��Ȃ��B
	if (nowAction == Define::rollAction_Basic::Idle)
		return nowDirectRight;
		*/
	// ���̃A�N�V������Ԃ�walk��������R���g���[���̓��͏�ԂŌ�����ς���B
	if (nowAction == Define::rollAction_Basic::Walk) {
		if (Controller::getIns()->getOnRight())
			return true;
		if (Controller::getIns()->getOnLeft())
			return false;
	}

	// ��L�̏�ԈȊO�̎��͌��݂̌������ێ�����B
	return nowDirectRight;

}