#pragma once
#include <DxLib.h>

/*!
@biref ���[�v���鏈���̒��S��S���N���X
@date 2020/04/15/15:12
@author mimuro
*/
class SystemLooper
{
public:
	SystemLooper() = default;
	~SystemLooper() = default;
	bool Error() const;
	bool scrProcess() const;
};

