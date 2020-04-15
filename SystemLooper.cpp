#include "SystemLooper.h"


SystemLooper::SystemLooper()//�R���X�g���N�^��shared_from_this()���g�p�ł��Ȃ��A�R���X�g���N�^�Ăяo�����ɂ͊��S�ɃI�u�W�F�N�g�𐶐��ł��Ă��Ȃ�
{}

bool SystemLooper::Initialize() //const�����Ă͂Ȃ�Ȃ��Aprivate�ȃ����o�ϐ���ύX���邩��
{
	scene.push(make_shared<Menu>(shared_from_this()));
	return true;
}

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

/*!
@brief ���[�v�̒��S�̏��������s�Bscene��top�����B
@date 2020/04/15/17:31
@author mimuro
*/
void SystemLooper::loop() const
{
	scene.top()->update();
	scene.top()->draw();
}

void SystemLooper::changeScene(eScene Next) const
{

}