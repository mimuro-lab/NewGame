#include "Enemy.h"

void Enemy::update(std::shared_ptr<Stage> _stage, Dimention shiftingStage, std::vector<std::shared_ptr<AbsDamageObj>> _damages)
{

	// �v���C���[�̍��W�����肵�Ă��瓖���蔻�������B���������t�ɂ���ƃG���[�B
	// Collision�̍X�V���s���B
	enemyStatus._y += shiftingStage.y;
	enemyStatus._x += shiftingStage.x;
	collision->update(enemyStatus, _stage);

	// Status�̍X�V�������s���B
	enemyStatus = animationMove->update(enemyStatus, animationSwitch->getNowAction(), collision, _stage, animation, controller);

	// �A�j���[�V�����̉��������s���B
	animation->update(enemyStatus);

	// �A�j���[�V�����̐؂�ւ����s���B�����؂�ւ��Ȃ���Γ���animation�I�u�W�F�N�g��Ԃ��B
	animation = animationSwitch->update(collision, animation, enemyStatus, controller);

	// �������X�V����B
	enemyStatus.directRight = enemyDirect->updateDirect(animationSwitch->getNowAction(), enemyStatus.directRight, enemyStatus, controller);

	if(_damages.size() == 0) {
		isAlive = true;
	}
	else {
		isAlive = false;
	}

}

void Enemy::draw()
{
	animation->draw();
	//collision->draw();
}