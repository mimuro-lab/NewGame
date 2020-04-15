#include "SystemLooper.h"

/*!
@brief SystemLooper�N���X�̃G���[����
@date 2020/04/15/15:27
@author mimuro
*/
bool SystemLooper::Error() const
{
	return false;
}

/*!
@brief �\��ʁE����ʏ����A���b�Z�[�W�����Ȃǂ��s���֐��B
@date 2020/04/15/15:27
@author mimuro
*/
bool SystemLooper::scrProcess() const
{
	if (ScreenFlip() != 0)
		return false;
	if (ProcessMessage() != 0)
		return false;
	if (ClearDrawScreen() != 0)
		return false;

	return true;
}