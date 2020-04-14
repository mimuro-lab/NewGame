#include <DxLib.h>
#include "SystemOwner.h"
#include <memory>
using namespace std;

/*!
@brief �v���W�F�N�g�̃��C���֐�
@date 2020/04/14/11:03
@author mimuro
*/
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	shared_ptr<SystemOwner> owner = make_shared<SystemOwner>();

	if (owner->initialize()) {
		owner->main();
	}

	owner->finalize();

	return 0;
}
