#pragma once

#include "Define.h"
#include "Pysical.h"
#include "CollisionDetect.h"

using namespace Define;

class PredictPoint
{

	// �X�V�O�̈ʒu
	Dimention nowPoint;

	// ���̃R�}�ňʒu����ł��낤���W
	Dimention predictPoint;

	Dimention calcPredictPoint(Dimention nowPoint, Dimention nowVelocity);

	int fittingPointHorizon(int nowX, int predictX, std::shared_ptr<CollisionDetect> _collision);

	int fittingPointVertical(int nowY, int predictY, std::shared_ptr<CollisionDetect> _collision);

public:
	PredictPoint() {
		predictPoint.x = predictPoint.y = 0;
		nowPoint.x = nowPoint.y =  0;
	}
	~PredictPoint() = default;

	Dimention update(Dimention nowPoint, Dimention nowVelocity, std::shared_ptr<CollisionDetect> _collision);

};