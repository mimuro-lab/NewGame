 #include "AnimationMove.h"

Define::Status AnimationMove::update(
	Define::Status nowStatus, 
	Define::rollAction_Basic _isAction, 
	std::shared_ptr<CollisionDetect> _collision, 
	std::shared_ptr<Stage> _stage, 
	std::shared_ptr<Animation> _animation
)
{
	Define::Status _nextStatus = nowStatus;

	CollisionDetect::toShiftDirect _to = getToShift(_isAction);
	
	if (getSwitchAction(_isAction))
		pysicQty.refresh(true, false);

	// ���̃R�}�ŁAy�����ɂ��̑��x�œ����đ��v���H������ǂ���������A�A�A
	if (_collision->calcShitingCollisionedSide(_to, pysicQty.y_vel) && !getForwardCollisionedSide(_to, _collision))
	{
		//bottom�ӂ�1�u���b�N��̃u���b�N�̉��Ӎ��W�Ɉړ�����B
		int x = nowStatus._x;
		int Forward_Block_nearSideY = getForwardBlockNearSide(nowStatus, _to, pysicQty, _collision, _stage);
		DrawBox(0, Forward_Block_nearSideY - 1, 1000, Forward_Block_nearSideY + 1, GetColor(255, 0, 0), true);
		int y = Forward_Block_nearSideY + getRangeOfNearBlock(_to, pysicQty, _collision);
		_collision->update(pysicQty.setPoint(nowStatus, x, y), _stage);
		pysicQty.refresh(true, true);
		return pysicQty.setPoint(nowStatus, x, y);
	}

	// ���x�̕����ɏ�ǂ������Ȃ�������pysicQty�̍X�V���s���B
	
	// _to�̕����ɉ����Ȃ��A���A_to�̕����ɍ��W���ړ����Ă���Ȃ�X�V
	bool forwardCollision = !getForwardCollisionedSide(_to, _collision);
	bool pysicShifting = pysicQty.getShifting(_to, _isAction);
	if (forwardCollision && pysicShifting) {
		return pysicQty.update(
				nowStatus,
				0, 
				getAcc(nowStatus, _isAction), 
				_isInitFroce[static_cast<int>(_isAction)], 
				_validGravityAction[static_cast<int>(_isAction)]
			);
	}
	
	return _nextStatus;
	
}

int AnimationMove::getForwardBlockNearSide(
	Define::Status nowStatus, 
	CollisionDetect::toShiftDirect _to, 
	PysicalQTY _pysic,
	std::shared_ptr<CollisionDetect> _collision, 
	std::shared_ptr<Stage> _stage
)
{
	switch (_to) {
	case CollisionDetect::toShiftDirect::head:
		return _stage->getBlockCell(nowStatus._x, nowStatus._y - _collision->getRange(_to) - Define::blockHeight).y2;
		break;
	case CollisionDetect::toShiftDirect::bottom:
		return _stage->getBlockCell(nowStatus._x, nowStatus._y + _collision->getRange(_to) + Define::blockHeight).y1;
		break;
	case CollisionDetect::toShiftDirect::_vertical://��������������W���ǂ����ɓ����Ă��邩�Ŕ��f�i���x�O�͂ǂ����ł��\��Ȃ�����ɍ��킹��j
		if(_pysic.y_vel <= 0)
			return _stage->getBlockCell(nowStatus._x, nowStatus._y - _collision->getRange(_to, _pysic.y_vel) - Define::blockHeight).y2;
		else
			return _stage->getBlockCell(nowStatus._x, nowStatus._y + _collision->getRange(_to, _pysic.y_vel) + Define::blockHeight).y1;
	}
	return 0;
}

//  _isAction�̏�Ԃłǂ̕����ɓ����A�N�V�����Ȃ̂����v�Z����B
CollisionDetect::toShiftDirect AnimationMove::getToShift(Define::rollAction_Basic _isAction)
{
	
	switch (_isAction) {
	case Define::rollAction_Basic::Brake:
		return CollisionDetect::toShiftDirect::_none;
		break;
	case Define::rollAction_Basic::Crouch:
		return CollisionDetect::toShiftDirect::_none;
		break;
	case Define::rollAction_Basic::Damage:
		return CollisionDetect::toShiftDirect::_none;
		break;
	case Define::rollAction_Basic::Idle:
		return CollisionDetect::toShiftDirect::_none;
		break;
	case Define::rollAction_Basic::Jump_Fall:
		return CollisionDetect::toShiftDirect::bottom;
		break;
	case Define::rollAction_Basic::Jump_Landing:
		return CollisionDetect::toShiftDirect::_none;
		break;
	case Define::rollAction_Basic::Jump_MidAir:
		return CollisionDetect::toShiftDirect::_vertical;
		break;
	case Define::rollAction_Basic::Jump_Up:
		return CollisionDetect::toShiftDirect::head;
		break;
	case Define::rollAction_Basic::Fall:
		return CollisionDetect::toShiftDirect::bottom;
		break;
	case Define::rollAction_Basic::Run:
		return CollisionDetect::toShiftDirect::_none;
		break;
	case Define::rollAction_Basic::Walk:
		return CollisionDetect::toShiftDirect::_none;
		break;
	}
	
	return CollisionDetect::toShiftDirect::_none;

}

bool AnimationMove::getForwardCollisionedSide(CollisionDetect::toShiftDirect _to, std::shared_ptr<CollisionDetect> _collision)

{
	switch (_to) {
	case CollisionDetect::toShiftDirect::head:
		return _collision->getCollisionedSide().head;
		break;
	case CollisionDetect::toShiftDirect::bottom:
		return _collision->getCollisionedSide().bottom;
		break;
	case CollisionDetect::toShiftDirect::_vertical:
		return _collision->getCollisionedSide().bottom || _collision->getCollisionedSide().head;
		break;
	}
	return false;
}

int AnimationMove::getRangeOfNearBlock(CollisionDetect::toShiftDirect _to, PysicalQTY _pysic, std::shared_ptr<CollisionDetect> _collision)
{
	switch (_to) {
	case CollisionDetect::toShiftDirect::head://��̃����K�ɍ��킹����̂ŉ������B
		return _collision->getRange(CollisionDetect::toShiftDirect::head);
		break;
	case CollisionDetect::toShiftDirect::bottom://���̃����K�ɍ��킹����̂ŏ�����B
		return -_collision->getRange(CollisionDetect::toShiftDirect::bottom);
		break;
	case CollisionDetect::toShiftDirect::_vertical://��������������W���ǂ����ɓ����Ă��邩�Ŕ��f�i���x�O�͂ǂ����ł��\��Ȃ�����ɍ��킹��j
		if (_pysic.y_vel <= 0)
			return _collision->getRange(CollisionDetect::toShiftDirect::head);
		else
			return -_collision->getRange(CollisionDetect::toShiftDirect::bottom);
		break;
	}
	return 0;
}

char AnimationMove::getAcc(Define::Status nowStatus, Define::rollAction_Basic _isAction)
{
	switch (_isAction) {
	case Define::rollAction_Basic::Jump_MidAir:
		return 0;
		break;
	case Define::rollAction_Basic::Jump_Up:
		return 0;
		break;
	case Define::rollAction_Basic::Fall:
		return 0;
		break;
	}
	return 0;
}

