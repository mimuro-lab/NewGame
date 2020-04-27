#include "CollisionDetect.h"

void CollisionDetect::update(Define::Status _nowStatus, std::shared_ptr<Stage> __stage)
{
	nowStatus = _nowStatus;
	_stage = __stage;
	
	collisionedSide.head = detectHead();

	collisionedSide.right = detectRight();

	collisionedSide.bottom = detectBottom();

	collisionedSide.left = detectLeft();

}

bool CollisionDetect::detectHead()
{
	for (int i = 0; i < headPoints; i++) {
		int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
		int y = nowStatus._y - toHead;
		if (IsDetectedStage(x, y))
			return true;
	}
	return false;
}

bool CollisionDetect::detectRight()
{
	for (int i = 0; i < headPoints; i++) {
		int x = nowStatus._x + toRight;
		int y = nowStatus._y - toHead + ((toHead + toBottom) / leftPoints) * i;
		if (IsDetectedStage(x, y)) 
			return true;
	}
	return false;
}

bool CollisionDetect::detectBottom()
{
	for (int i = 0; i < rightPoints; i++) {
		int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
		int y = nowStatus._y + toBottom;
		if (IsDetectedStage(x, y)) 
			return true;
	}
	return false;
}

bool CollisionDetect::detectLeft()
{
	for (int i = 0; i < leftPoints; i++) {
		int x = nowStatus._x - toLeft;
		int y = nowStatus._y - toHead + ((toHead + toBottom) / leftPoints) * i;
		if (IsDetectedStage(x, y)) 
			return true;
	}
	return false;
}

void CollisionDetect::draw()
{
	// head
	for (int i = 0; i < headPoints; i++) {
		int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
		int y = nowStatus._y - toHead;
		unsigned int color = GetColor(255, 255, 255);
		if (IsDetectedStage(x, y))
			color = GetColor(255, 0, 0);
		DrawCircle(x, y, 2, color, false);
	}

	// bottom
	for (int i = 0; i < bottomPoints; i++) {
		int x = nowStatus._x - toLeft + ((toLeft + toRight) / bottomPoints) * i;
		int y = nowStatus._y + toBottom;
		unsigned int color = GetColor(255, 255, 255);
		if (IsDetectedStage(x, y))
			color = GetColor(255, 0, 0);
		DrawCircle(x, y, 2, color, false);
	}
	
	// right
	for (int i = 0; i < rightPoints; i++) {
		int x = nowStatus._x + toRight;
		int y = nowStatus._y - toHead + ((toHead + toBottom) / rightPoints) * i;
		unsigned int color = GetColor(255, 255, 255);
		if (IsDetectedStage(x, y))
			color = GetColor(255, 0, 0);
		DrawCircle(x, y, 2, color, false);
	}

	// left
	for (int i = 0; i < leftPoints; i++) {
		int x = nowStatus._x - toLeft;
		int y = nowStatus._y - toHead + ((toHead + toBottom) / leftPoints) * i;
		unsigned int color = GetColor(255, 255, 255);
		if (IsDetectedStage(x, y))
			color = GetColor(255, 0, 0);
		DrawCircle(x, y, 2, color, false);
	}
	
}

bool CollisionDetect::IsDetectedStage(int x, int y)
{
	// x, y���W���X�e�[�W�̂ǂ̃C���f�b�N�X�ɒl���邩�H
	char _CellXNum = (x - _stage->getPointLeftUpX()) / _stage->getBlockWidth();
	char _CellYNum = (y - _stage->getPointLeftUpY()) / _stage->getBlockHeight();

	//�X�e�[�W�䂩��͂ݏo��Ȃ�ǂɏՓ˂����Ƃ������ƁB
	if (_CellXNum < 0 || _CellYNum < 0 || _CellXNum >= _stage->getBlockXNum() || _CellYNum >= _stage->getBlockYNum()) {
		DrawCircle(x, y, 30, GetColor(0, 255, 255), false);
		return false;
	}

	// �����Ax, y�ɂ���X�e�[�W�̗v�f��block��������Փ˂Ɣ���B
	if (_stage->getStage()[_CellXNum][_CellYNum]._status == Define::BlockCell::cellStatus::block) {
		return true;
	}

	// �ǂ��ɂ��Փ˂��Ȃ����false��Ԃ��B
	return false;
}

// range�������ɏ�ǂ���������true
bool CollisionDetect::calcShitingCollisionedSideVertical(toShiftDirect _to, char _range)
{
	// range��0��������1��𒲂ׂ�
	if (_range == 0) {
		switch (_to) {
			case toShiftDirect::head:
				for (int i = 0; i <= headPoints; i++) {
					int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
					int y = nowStatus._y - toHead - 1;
					if (IsDetectedStage(x, y)) 
						return true;
				}
				return false;
				break;
		}
		return false;
	}

	if (_to != toShiftDirect::_vertical)
		_range = std::abs(_range);

	collisionSideRange.bottom = collisionSideRange.head = collisionSideRange.right = collisionSideRange.left = 0;
	
	// _range���u���b�N�̕��𒴂��Ă��܂��Ă�����A�v���C���[�I�u�W�F�N�g��Botton����_stage->blockHeight�����ǂ̗L���𒲂ׂ�B

	unsigned char BlocksIn_range = 0;//_range�̒��ɂ����̃u���b�N�����邩�H

	if (_range > _stage->blockHeight)
		BlocksIn_range = _range / _stage->blockHeight;

	switch (_to) {
	case toShiftDirect::head:
		for (int i = 0; i < headPoints; i++) {
			int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
			int y = nowStatus._y - toBottom - _range;
			if (IsDetectedStage(x, y))
				return true;
		}
		return false;
		break;
	case toShiftDirect::bottom:
		// _range�̒��ɏ�ǂ��Ȃ������ׂ�BBlocksIn_range��p����B
		for(int block = 0; block < BlocksIn_range; block++)
			for (int i = 0; i < bottomPoints; i++) {
				int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
				int y = nowStatus._y + toBottom + block * _stage->blockHeight; 
				if (IsDetectedStage(x, y)) {
					collisionSideRange.bottom = block * _stage->blockHeight;
					return true;
				}
			}

		DrawBox(nowStatus._x - 20, nowStatus._y - 40, nowStatus._x + 20, nowStatus._y + 40, GetColor(255, 0, 0), false);
		for (int i = 0; i < rightPoints; i++) {	
			int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
			int y = nowStatus._y + toBottom + _range;
			DrawCircle(x, y, 3, GetColor(255, 0, 0), false);
			if (IsDetectedStage(x, y)) {
				collisionSideRange.bottom = _range;
				return true;
			}
		}
		return false;
		break;
	case toShiftDirect::_vertical://_range�̌����ɂ���āA�ォ���𒲂ׂ�
		//������̏ꍇ
		if (_range < 0) {
			for (int i = 0; i < headPoints; i++) {
				int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
				int y = nowStatus._y - toBottom - _range;
				if (IsDetectedStage(x, y))
					return true;
			}
		}
		//�������̏ꍇ
		if (_range > 0) {
			for (int block = 0; block < BlocksIn_range; block++)
				for (int i = 0; i < bottomPoints; i++) {
					int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
					int y = nowStatus._y + toBottom + block * _stage->blockHeight;
					if (IsDetectedStage(x, y)) {
						collisionSideRange.bottom = block * _stage->blockHeight;
						return true;
					}
				}

			DrawBox(nowStatus._x - 20, nowStatus._y - 40, nowStatus._x + 20, nowStatus._y + 40, GetColor(255, 0, 0), false);
			for (int i = 0; i < rightPoints; i++) {
				int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
				int y = nowStatus._y + toBottom + _range;
				DrawCircle(x, y, 3, GetColor(255, 0, 0), false);
				if (IsDetectedStage(x, y)) {
					collisionSideRange.bottom = _range;
					return true;
				}
			}
		}
		return false;
		break;
	}
	
	//�G���[�����A�Ƃ肠�����Ԃ����Ă��鎖�ɂ���B
	return true;
}

bool CollisionDetect::calcShitingCollisionedSideHorizon(toShiftDirect _to, char _range)
{

	//if (_range == 0)
		//return false;
	// range��0��������A1��̍��W�𒲂ׂ�B
	if (_range == 0) {
		switch (_to) {
		case CollisionDetect::toShiftDirect::left:
			for (int i = 0; i < leftPoints - 1; i++) {
				int x = nowStatus._x - toLeft - 1;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
				if (IsDetectedStage(x, y))
					return true;
			}
			break;
		case CollisionDetect::toShiftDirect::right:
			for (int i = 0; i < rightPoints - 1; i++) {
				int x = nowStatus._x + toLeft + 1;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
				if (IsDetectedStage(x, y))
					return true;
			}
			break;
		case CollisionDetect::toShiftDirect::_none:
			for (int i = 0; i < leftPoints - 1; i++) {
				int x = nowStatus._x - toLeft - 1;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
				if (IsDetectedStage(x, y))
					return true;
			}
			for (int i = 0; i < rightPoints - 1; i++) {
				int x = nowStatus._x + toLeft + 1;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
				if (IsDetectedStage(x, y))
					return true;
			}
			return false;
		case CollisionDetect::toShiftDirect::bottom:
			for (int i = 0; i < leftPoints - 1; i++) {
				int x = nowStatus._x - toLeft - 1;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
				if (IsDetectedStage(x, y))
					return true;
			}
			for (int i = 0; i < rightPoints - 1; i++) {
				int x = nowStatus._x + toLeft + 1;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
				if (IsDetectedStage(x, y))
					return true;
			}
			return false;
		case CollisionDetect::toShiftDirect::head:
			for (int i = 0; i < leftPoints - 1; i++) {
				//int x = nowStatus._x - toLeft - 1;
				int y = nowStatus._y - toHead - 1;
				int senceHeight = (toLeft + toRight) / headPoints;
				int x = nowStatus._x - toLeft + senceHeight * i;
				//int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
				if (IsDetectedStage(x, y))
					return true;
			}
			for (int i = 0; i < rightPoints - 1; i++) {
				int x = nowStatus._x + toLeft + 1;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
				if (IsDetectedStage(x, y))
					return true;
			}
			return false;
		case CollisionDetect::toShiftDirect::_vertical:
			for (int i = 0; i < leftPoints - 1; i++) {
				int x = nowStatus._x - toLeft - 1;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
				if (IsDetectedStage(x, y))
					return true;
			}
			for (int i = 0; i < rightPoints - 1; i++) {
				int x = nowStatus._x + toLeft + 1;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
				if (IsDetectedStage(x, y))
					return true;
			}
			return false;
		}
	}

	if (_to != toShiftDirect::_holizen)
		_range = std::abs(_range);

	//collisionSideRange.bottom = collisionSideRange.head = collisionSideRange.right = collisionSideRange.left = 0;

	// _range���u���b�N�̕��𒴂��Ă��܂��Ă�����A�v���C���[�I�u�W�F�N�g��Botton����_stage->blockWidth�����ǂ̗L���𒲂ׂ�B
	unsigned char BlocksIn_range = 0;//_range�̒��ɂ����̃u���b�N�����邩�H

	if (_range > _stage->blockWidth)
		BlocksIn_range = _range / _stage->blockWidth;

	switch (_to) {
	case toShiftDirect::right:
		for (int i = 0; i < rightPoints - 1; i++) {
			int x = nowStatus._x + toRight + _range;
			int senceHeight = (toHead + toBottom) / rightPoints;
			int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
			DrawCircle(x, y, 1, GetColor(0, 255, 0), true);
			if (IsDetectedStage(x, y))
				return true;
		}
		return false;
		break;

	case toShiftDirect::left:
		for (int i = 0; i < leftPoints - 1; i++) {
			int x = nowStatus._x - toLeft - _range;
			int senceHeight = (toHead + toBottom) / rightPoints;
			int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
			DrawCircle(x, y, 1, GetColor(0, 255, 0), true);
			if (IsDetectedStage(x, y))
				return true;
		}
		return false;
		break;

	case toShiftDirect::_holizen://���x�ɂ���āA�E�����𒲂ׂ�
		if (_range > 0) {
			for (int i = 0; i < rightPoints; i++) {
				int x = nowStatus._x + toRight + _range;
				int y = nowStatus._y - toHead + ((toHead + toBottom) / rightPoints) * i;
				if (IsDetectedStage(x, y))
					return true;
			}
		}
		if (_range > 0) {
			for (int i = 0; i < leftPoints; i++) {
				int x = nowStatus._x - toLeft - _range;
				int y = nowStatus._y - toHead + ((toHead + toBottom) / leftPoints) * i;
				if (IsDetectedStage(x, y))
					return true;
			}
		}
		return false;
		break;

	case CollisionDetect::toShiftDirect::head:
		for (int i = 0; i < rightPoints - 1; i++) {
			int x = nowStatus._x + toRight + _range;
			int senceHeight = (toHead + toBottom) / rightPoints;
			int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
			DrawCircle(x, y, 1, GetColor(0, 255, 0), true);
			if (IsDetectedStage(x, y))
				return true;
		}
		for (int i = 0; i < leftPoints - 1; i++) {
			int x = nowStatus._x - toLeft - _range;
			int senceHeight = (toHead + toBottom) / leftPoints;
			int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
			DrawCircle(x, y, 1, GetColor(0, 255, 0), true);
			if (IsDetectedStage(x, y))
				return true;
		}
		return false;
	case CollisionDetect::toShiftDirect::_vertical:
		for (int i = 0; i < rightPoints - 1; i++) {
			int x = nowStatus._x + toRight + _range;
			int senceHeight = (toHead + toBottom) / rightPoints;
			int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
			DrawCircle(x, y, 1, GetColor(0, 255, 0), true);
			if (IsDetectedStage(x, y))
				return true;
		}
		for (int i = 0; i < leftPoints - 1; i++) {
			int x = nowStatus._x - toLeft - _range;
			int senceHeight = (toHead + toBottom) / leftPoints;
			int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
			DrawCircle(x, y, 1, GetColor(0, 255, 0), true);
			if (IsDetectedStage(x, y))
				return true;
		}
		return false;
	case CollisionDetect::toShiftDirect::bottom:
		for (int i = 0; i < rightPoints - 1; i++) {
			int x = nowStatus._x + toRight + _range;
			int senceHeight = (toHead + toBottom) / rightPoints;
			int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
			DrawCircle(x, y, 1, GetColor(0, 255, 0), true);
			if (IsDetectedStage(x, y))
				return true;
		}
		for (int i = 0; i < leftPoints - 1; i++) {
			int x = nowStatus._x - toLeft - _range;
			int senceHeight = (toHead + toBottom) / leftPoints;
			int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
			DrawCircle(x, y, 1, GetColor(0, 255, 0), true);
			if (IsDetectedStage(x, y))
				return true;
		}
		return false;
	}

	//�G���[�����A�Ƃ肠�����Ԃ����Ă��鎖�ɂ���B
	return false;
}

const char CollisionDetect::getRange(toShiftDirect _to, int y_vel, int x_vel)
{
	switch (_to) {
	case toShiftDirect::head:
		return toHead;
		break;
	case toShiftDirect::bottom:
		return toBottom;
		break;
	case toShiftDirect::right:
		return toRight;
		break;
	case toShiftDirect::left:
		return toLeft;
		break;
	case toShiftDirect::_vertical://��������������W���ǂ����ɓ����Ă��邩�Ŕ��f�i���x�O�͂ǂ����ł��\��Ȃ�����ɍ��킹��j
		if (y_vel <= 0)
			return toHead;
		else
			return toBottom;

	case toShiftDirect::_holizen://��������������W���ǂ����ɓ����Ă��邩�Ŕ��f�i���x�O�͂ǂ����ł��\��Ȃ������ɍ��킹��j
		if (x_vel <= 0)
			return toLeft;
		else
			return toRight;
	case toShiftDirect::_none://��~��Ԃł���ׂ����͉��̃u���b�N�ɍ��킹��
		return toBottom;
		break;
	}

	return 0;
}