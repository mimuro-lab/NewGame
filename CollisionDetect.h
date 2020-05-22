
/*!
@file CollisionDetect.h
@brief CollisionDetect�N���X����`����Ă���w�b�_�t�@�C��
@date 2020/05/04/16:21
@author mimuro
*/

#pragma once

#include <vector>
#include <memory>
#include <DxLib.h>
#include "Define.h"
#include "Stage.h"

/*!
@class CollisionDetect
@brief �����蔻�菈�����s���N���X�B
@date 2020/05/04/16:21
@author mimuro
*/

using namespace Define;
using namespace std;

class CollisionDetect
{
	//! �����蔻����i�[����ϐ��BTrue���Ɠ������Ă���B
	struct Collision {
		bool head;
		bool bottom;
		bool right;
		bool left;
	};

	//! ���S���W����ǂ̂��炢�͈̔͂œ����蔻���u�����B���͈̔͂̒l���Ǘ�����\���́B
	struct Collision_range {
		unsigned char head = 0;
		unsigned char bottom = 0;
		unsigned char right = 0;
		unsigned char left = 0;
	};

	//! �����蔻����Ǘ�����ϐ��B
	Collision collisionedSide;

	// �v���C���[�I�u�W�F�N�g�̒��S�_����ɂ��A�ǂ̂��炢�̒����œ����蔻���u�����B
	char toRight = 10;
	char toLeft = 10;
	char toHead = 15;
	char toBottom = 30;

	// �e�ӂɒu�������蔻��̓_�̐��B
	char rightPoints = 10;
	char leftPoints = 10;
	char headPoints = 10;
	char bottomPoints = 10;

	//! ���݂̃v���C���[�̏�Ԃ��i�[����ϐ��B
	Status nowStatus;

	//! �X�e�[�W�̏�Ԃ��󂯎��ϐ��B
	shared_ptr<Stage> _stage;

	//! �p����ǂɓ������Ă��邩�̃t���O
	bool isCollisionedEdge = false;

	//! (x, y)���W�͉����ɓ������Ă��邩�ǂ���
	bool IsDetectedStage(int x, int y, shared_ptr<Stage> stage);

	//! head�����̏Փ˂̗L�����m�F����B
	bool detectHead(shared_ptr<Stage> stage, Status nowStatus);

	//! right�����̏Փ˂̗L�����m�F����B
	bool detectRight(shared_ptr<Stage> stage, Status nowStatus);

	//! bottom�����̏Փ˂̗L�����m�F����B
	bool detectBottom(shared_ptr<Stage> stage, Status nowStatus);

	//! left�����̏Փ˂̗L�����m�F����B
	bool detectLeft(shared_ptr<Stage> stage, Status nowStatus);

public:
	CollisionDetect(shared_ptr<Stage> __stage, Status _status) {
		// �����蔻�菈���͍ŏ������ɂ���B
		collisionedSide.head = false;
		collisionedSide.bottom = false;
		collisionedSide.right = false;
		collisionedSide.left = false;
		_stage = __stage;
		nowStatus = _status;
	};
	~CollisionDetect() = default;

	//! �����蔻��͈̔͂��i�[����ϐ��B
	Collision_range collisionSideRange;

	//! �X�V�������s���֐��B
	void update(Status _nowStatus, shared_ptr<Stage> _stage);

	//! �����蔻��ɂ�����A�����̒�`�B
	enum class toShiftDirect{
		right, left, head, bottom
	};

	//! ���������ŁA�C�ӂ̋����ɏ�ǂ����邩�ǂ����𒲂ׂ�֐��B
	bool calcShitingCollisionedSideVertical(toShiftDirect _to, char _range, char _horizonal_range);

	//! ���������ŁA�C�ӂ̋����ɏ�ǂ����邩�ǂ����𒲂ׂ�֐��B
	bool calcShitingCollisionedSideHorizon(toShiftDirect _to, char _range, char _vertical_range);

	void draw();

	//! �����蔻����擾����֐��B
	Collision getCollisionedSide() { 
		return collisionedSide; 
	}
	//! ���S���W����̓����蔻��͈̔͂�Ԃ��֐��B
	const char getRange(toShiftDirect _to);

	const bool getIsCollisionedEdge() { return isCollisionedEdge; }

};
