#pragma once

#include <memory>
#include <vector>
#include "Define.h"
#include "CollisionDetect.h"
#include "Animation.h"
#include "Pysical.h"
#include "PredictPoint.h"

using namespace Define;

class AnimationMove
{
	Pysical pysical;

	PredictPoint predictPoint;

	// ���݂̑��x�i�����蔻��ɂ��A���ꂪ���̂܂ܗL���ɂȂ�Ƃ͌���Ȃ��j
	Dimention nowVelocity;

	// ���ۂɗL���ɂȂ鑬�x
	Dimention validVelocity;

	// ���̍��W�i�X�V�����O�̍��W�j
	Dimention nowPoint;

	// ���̍��W
	Dimention nextPoint;

public:
	AnimationMove(char _walk, char _run, char _jumpUp, char _jumpMidAir){

		nowVelocity.x = nowVelocity.y = 0;

	};

	~AnimationMove() = default;

	Define::Status update(Define::Status nowStatus, Define::rollAction_Basic _isAction, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage, std::shared_ptr<Animation> _animation);

};

