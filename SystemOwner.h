#pragma once
#include <DxLib.h>
#include "Define.h"

/*!
@brief ������������I�������S�ʂ�S���N���X
@date 2020/04/14/23:43
@author mimuro
*/

class SystemOwner
{
public:
	/*!
	@brief �R���X�g���N�^��default�錾���闝�R��http://www.linktracktool.com/cpp/default-ctor.html�Q��
	*/
	SystemOwner() = default;
	~SystemOwner() = default;
	bool initialize() const;
	bool finalize() const;

	bool main() const;

};

