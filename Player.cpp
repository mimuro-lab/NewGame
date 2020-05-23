
/*!
@file Player.cpp
@brief Player�N���X���̃����o�ނ̒�`���s��CPP�t�@�C���B
@date 2020/04/21/12:34
@author mimuro
*/

#include "Player.h"

VirtualController Player::updateController()
{
	VirtualController retController;

	retController.on_A = Controller::getIns()->getOn_A();
	retController.on_B = Controller::getIns()->getOn_B();
	retController.on_X = Controller::getIns()->getOn_X();
	retController.on_Y = Controller::getIns()->getOn_Y();

	retController.push_A = Controller::getIns()->getPush_A();
	retController.push_B = Controller::getIns()->getPush_B();
	retController.push_X = Controller::getIns()->getPush_X();
	retController.push_Y = Controller::getIns()->getPush_Y();

	retController.on_right = Controller::getIns()->getOnRight();
	retController.on_left = Controller::getIns()->getOnLeft();
	retController.on_up = Controller::getIns()->getOnUp();
	retController.on_down = Controller::getIns()->getOnDown();

	retController.push_right = Controller::getIns()->getPushRight();
	retController.push_left = Controller::getIns()->getPushLeft();
	retController.push_up = Controller::getIns()->getPushUp();
	retController.push_down = Controller::getIns()->getPushDown();

	return retController;

}

/*!
@brief �v���C���[�I�u�W�F�N�g�̍��W�X�V�A�A�j���[�V�����̏����Ȃǂ��s���B
@date 2020/04/21/12:36
@author mimuro
*/
void Player::update(std::shared_ptr<Stage> _stage)
{

	controller = updateController();

	// �v���C���[�̍��W�����肵�Ă��瓖���蔻�������B���������t�ɂ���ƃG���[�B
	// Collision�̍X�V���s���B
	collision->update(playerStatus, _stage);

	// Status�̍X�V�������s���B
	playerStatus = animationMove->update(playerStatus, animationSwitch->getNowAction(), collision, _stage, animation);

	// shiftingStage�̍X�V�������s���B
	shiftingStage = animationMove->getShiftingStage(collision, _stage);

	// �A�j���[�V�����̉��������s���B
	animation->update(playerStatus);
	
	// �A�j���[�V�����̐؂�ւ����s���B�����؂�ւ��Ȃ���Γ���animation�I�u�W�F�N�g��Ԃ��B
	animation = animationSwitch->update(collision, animation, playerStatus, controller);

	// �������X�V����B
	playerStatus.directRight = playerDirect->updateDirect(animationSwitch->getNowAction(), playerStatus.directRight, playerStatus, controller);

}

void Player::draw()
{
	animation->draw();
	//collision->draw();
}

vector<shared_ptr<DamageObj>> Player::generateDamageObj(vector<shared_ptr<DamageObj>> _nowDmg)
{
	vector<shared_ptr<DamageObj>> returnDmg = _nowDmg;

	if (controller.on_up) {
		shared_ptr<DamageObj> pushObj = make_shared<DamageObj>(playerStatus._x, playerStatus._y, 10);
		returnDmg.push_back(pushObj);
	}

	return returnDmg;
}