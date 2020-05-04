
/*!
@file CollisionDetect.cpp
@brief CollisionDetect�N���X���̃����o�ނ̒�`���s��CPP�t�@�C���B
@date 2020/05/04/16:36
@author mimuro
*/

#include "CollisionDetect.h"

/*!
@par ����E�����E�E���E�����̓����蔻��𒲂ׂ�֐��B����return���Ȃ��B
@date 2020/05/04/16:40
@author mimuro
*/
void CollisionDetect::update(Define::Status _nowStatus, std::shared_ptr<Stage> __stage)
{
	nowStatus = _nowStatus;
	_stage = __stage;
	
	collisionedSide.head = detectHead();

	collisionedSide.right = detectRight();

	collisionedSide.bottom = detectBottom();

	collisionedSide.left = detectLeft();

}


/*!
@par ����̓����蔻��𒲂ׂ�֐��B��ǂ���������true��Ԃ��B
@date 2020/05/04/16:40
@author mimuro
*/
bool CollisionDetect::detectHead()
{
	for (int i = 0; i < headPoints; i++) {
		// �u���b�N��0 �` blockHeight - 1�P�ʂŐ��������̂ŁA�����𒲂ׂ�ۂ�-1����
		int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
		int y = nowStatus._y - toHead - 1;
		if (IsDetectedStage(x, y))
			return true;
	}
	return false;
}

/*!
@par �E���̓����蔻��𒲂ׂ�֐��B��ǂ���������true��Ԃ��B
@date 2020/05/04/16:40
@author mimuro
*/
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

/*!
@par �����̓����蔻��𒲂ׂ�֐��B��ǂ���������true��Ԃ��B
@date 2020/05/04/16:40
@author mimuro
*/
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

/*!
@par �����̓����蔻��𒲂ׂ�֐��B��ǂ���������true��Ԃ��B
@date 2020/05/04/16:40
@author mimuro
*/
bool CollisionDetect::detectLeft()
{
	for (int i = 0; i < leftPoints; i++) {
		// �u���b�N��0 �` blockWidth - 1�P�ʂŐ��������̂ŁA�����𒲂ׂ�ۂ�-1����
		int x = nowStatus._x - toLeft - 1;
		int y = nowStatus._y - toHead + ((toHead + toBottom) / leftPoints) * i;
		if (IsDetectedStage(x, y)) 
			return true;
	}
	return false;
}

/*!
@par �����蔻��̕`����s���֐��B�����Ԃ��Ȃ��B
@date 2020/05/04/16:40
@author mimuro
*/
void CollisionDetect::draw()
{
	// head
	for (int i = 0; i < headPoints; i++) {
		int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
		int y = nowStatus._y - toHead - 1;
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
		int x = nowStatus._x - toLeft - 1;
		int y = nowStatus._y - toHead + ((toHead + toBottom) / leftPoints) * i;
		unsigned int color = GetColor(255, 255, 255);
		if (IsDetectedStage(x, y))
			color = GetColor(255, 0, 0);
		DrawCircle(x, y, 2, color, false);
	}
	
}

/*!
@par x,y���W�ɃX�e�[�W�̃u���b�N�����邩�ǂ����B
@date 2020/05/04/16:40
@author mimuro
*/
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

/*!
@par ���������ɂ����āA_to�̕�����_range����ɏ�ǂ����邩�ǂ����𔻒f����֐��B
@brief _range��1�u���b�N���𒴂��Ă�����A_to�̕�������_range�܂ł̊Ԃ��u���b�N�̗L���𔻒肷��B
@date 2020/05/04/16:57
@author mimuro
*/
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
				DrawCircle(x, y, 3, GetColor(255, 255, 255), true);
				if (IsDetectedStage(x, y)) {
					collisionSideRange.bottom = block * _stage->blockHeight;
					return true;
				}
			}

		DrawBox(nowStatus._x - 20, nowStatus._y - 40, nowStatus._x + 20, nowStatus._y + 40, GetColor(255, 0, 0), false);
		for (int i = 0; i < rightPoints; i++) {	
			int x = nowStatus._x - toLeft + ((toLeft + toRight) / headPoints) * i;
			int y = nowStatus._y + toBottom + _range;
			
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

/*!
@par ���������ɂ����āA_to�̕�����_range����ɏ�ǂ����邩�ǂ����𔻒f����֐��B
@brief _range��1�u���b�N���𒴂��Ă�����A_to�̕�������_range�܂ł̊Ԃ��u���b�N�̗L���𔻒肷��B
@date 2020/05/04/16:58
@author mimuro
*/
bool CollisionDetect::calcShitingCollisionedSideHorizon(toShiftDirect _to, char _range)
{
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
		}
	}


	// _range���u���b�N�̕��𒴂��Ă��܂��Ă�����A�v���C���[�I�u�W�F�N�g��Botton����_stage->blockWidth�����ǂ̗L���𒲂ׂ�B
	unsigned char BlocksIn_range = 1;//_range�̒��ɂ����̃u���b�N�����邩�H

	if (std::abs(_range) > _stage->blockWidth)
		BlocksIn_range = std::abs(_range) / _stage->blockWidth + 1;

	switch (_to) {
	case toShiftDirect::right:
		// _range�̒��ɏ�ǂ��Ȃ������ׂ�BBlocksIn_range��p����B
		for (int block = 0; block < BlocksIn_range; block++)
			for (int i = 0; i < rightPoints; i++) {
				int x = nowStatus._x + toRight + _range + Define::blockWidth * block;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
				DrawCircle(x, y, 1, GetColor(0, 255, 0), true);
				if (IsDetectedStage(x, y))
					return true;
			}
		break;

	case toShiftDirect::left:
		// _range�̒��ɏ�ǂ��Ȃ������ׂ�BBlocksIn_range��p����B
		for (int block = 0; block < BlocksIn_range; block++)
			for (int i = 0; i < leftPoints; i++) {
				int x = nowStatus._x - toLeft - std::abs(_range) - Define::blockWidth * block;
				int senceHeight = (toHead + toBottom) / rightPoints;
				int y = nowStatus._y - toHead + senceHeight * i + senceHeight / 2;
				DrawCircle(x, y, 1, GetColor(0, 255, 0), true);
				if (IsDetectedStage(x, y))
					return true;
			}
		break;
	}

	//�G���[�����A�Ƃ肠�����Ԃ����Ă��鎖�ɂ���B
	return false;
}

/*!
@par _to�̕����́A���S���W����̓����蔻��͈̔͂�Ԃ��֐��B
@date 2020/05/04/16:59
@author mimuro
*/
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