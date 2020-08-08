#include "Enemy.h"

void Enemy::update(std::shared_ptr<Stage> _stage, Dimention shiftingStage, std::vector<std::shared_ptr<AbsDamageObj>> _damages)
{
	statusAsChara._y += shiftingStage.y;
	statusAsChara._x += shiftingStage.x;

	if (statusAsChara._x < 0 + deActiveLeft 
		|| statusAsChara._x > WIN_W + deActiveRight
		|| statusAsChara._y < 0 + deActiveHead
		|| statusAsChara._y > WIN_H + deActiveBottom)
		statusAsPara->isActive = false;
	else
		statusAsPara->isActive = true;

	if (!statusAsPara->isActive)
		return;


	// �v���C���[�̍��W�����肵�Ă��瓖���蔻�������B���������t�ɂ���ƃG���[�B
	// Collision�̍X�V���s���B
	collision->update(statusAsChara, _stage);
	collisionPoints = collision->getCollisionPoints();

	bool isDetectedDamages = false;
	isDetectedDamages = damagesOverlap->isOverlaped(collisionPoints, _damages);
	if(isDetectedDamages)
		DrawCircle(statusAsChara._x, statusAsChara._y, 50, GetColor(255, 255, 255), false);

	// Status�̍X�V�������s���B
	statusAsChara = animationMove->update(statusAsChara, animationSwitch->getNowAction(), collision, _stage, animation, controller);

	// �A�j���[�V�����̉��������s���B
	animation->update(statusAsChara);

	// �A�j���[�V�����̐؂�ւ����s���B�����؂�ւ��Ȃ���Γ���animation�I�u�W�F�N�g��Ԃ��B
	animation = animationSwitch->update(collision, animation, statusAsChara, controller);

	// �������X�V����B
	statusAsChara.directRight = enemyDirect->updateDirect(animationSwitch->getNowAction(), statusAsChara.directRight, statusAsChara, controller);

}

void Enemy::adjustBottom(int AdjustRange)
{
	statusAsChara._y += AdjustRange;
}

void Enemy::draw()
{
	animation->draw();
	//collision->draw();

	//DrawFormatString(statusAsChara._x, statusAsChara._y, GetColor(255, 255, 255), "%d %d", statusAsChara._x, statusAsChara._y);

}