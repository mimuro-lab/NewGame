#include "DxLib.h"

/*!
@brief �v���W�F�N�g�̃��C���֐�
@date 2020/04/14/11:03
@author mimuro
*/
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	DxLib_Init();	// DX���C�u��������������
	WaitKey();	// �L�[���͑҂�
	DxLib_End();	// DX���C�u�����I������
	return 0;
}