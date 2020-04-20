#pragma once

#include "Singleton.h"
#include <array>

class Gamepad
{
	const static int PAD_KEY_NUM = 16;

	//! �ǂ̃{�^�����ǂ̃{�^���Ɋ��蓖�����Ă��邩������
	std::array<int, PAD_KEY_NUM> _idArray = { 0 };
	
	//! 16�{�^����pad���͏�Ԋi�[
	std::array<int, PAD_KEY_NUM> _pad = { 0 };
protected:

	Gamepad();
	~Gamepad() = default;

	enum ePad {
		left,
		right,
		up,
		down,
		sikaku,
		maru,
		sankaku,
		batu,
		start,
		select
	};

	void update();

	//! eID�̃{�^���̓��͏�Ԃ��擾
	int get(ePad eID) const;
};

