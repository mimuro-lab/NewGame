
/*!
@file PlayerDirect.h
@brief PlayerDirect�N���X����`����Ă���w�b�_�t�@�C��
@date 2020/05/04/17:43
@author mimuro
*/

#pragma once
#include "Define.h"
#include "Controller.h"

/*!
@class PlayerDirect
@brief Player�L�����̕������X�V����N���X�B
@date 2020/05/04/17:43
@author mimuro
*/
class PlayerDirect
{
public:
	PlayerDirect() = default;
	~PlayerDirect() = default;

	//! �X�V�������s���֐��B
	bool updateDirect(Define::rollAction_Basic nowAction, bool nowDirectRight);
};