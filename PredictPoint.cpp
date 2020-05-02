#include "PredictPoint.h"

Dimention PredictPoint::calcPredictPoint(Dimention nowPoint, Dimention nowVelocity)
{
	Dimention returnPoint = nowPoint;

	returnPoint.x += nowVelocity.x;
	returnPoint.y += nowVelocity.y;

	return returnPoint;

}

int PredictPoint::fittingPointHorizon(int nowX, int predictX, std::shared_ptr<CollisionDetect> _collision)
{

	int returnX = nowX;

	// predictX�����݈ʒu���E��������
	if (nowX < predictX) {
		int shiftedX = predictX + _collision->getRange(CollisionDetect::toShiftDirect::right);
		if (!_collision->calcShitingCollisionedSideVertical(CollisionDetect::toShiftDirect::right, shiftedX))
			returnX = predictX;
	}

	// predictX�����݈ʒu��荶��������
	if (nowX > predictX) {
		int shiftedX = predictX - _collision->getRange(CollisionDetect::toShiftDirect::left);
		if (!_collision->calcShitingCollisionedSideVertical(CollisionDetect::toShiftDirect::left, shiftedX))
			returnX = predictX;
	}

	return returnX;
}

int PredictPoint::fittingPointVertical(int nowY, int predictY, std::shared_ptr<CollisionDetect> _collision)
{
	int returnY = nowY;

	// predictY�����݈ʒu��艺��������
	if (nowY < predictY) {
		int shiftedY = predictY - nowY;
		bool isCollisionedPredictBottom = _collision->calcShitingCollisionedSideVertical(CollisionDetect::toShiftDirect::bottom, shiftedY);
		if (!isCollisionedPredictBottom) {
			returnY = predictY;
		}
		else {
			int a;
		}
	}

	// predictY�����݈ʒu���ゾ������
	if (nowY > predictY) {
		int shiftedY = predictY - _collision->getRange(CollisionDetect::toShiftDirect::head);
		if (!_collision->calcShitingCollisionedSideVertical(CollisionDetect::toShiftDirect::head, shiftedY))
			returnY = predictY;
		else {
			int a;
		}
	}

	return returnY;
}

Dimention PredictPoint::update(Dimention _nowPoint, Dimention nowVelocity, std::shared_ptr<CollisionDetect> _collision)
{

	nowPoint = _nowPoint;

	predictPoint = calcPredictPoint(nowPoint, nowVelocity);

	predictPoint.x = fittingPointHorizon(nowPoint.x, predictPoint.x, _collision);

	predictPoint.y = fittingPointVertical(nowPoint.y, predictPoint.y, _collision);

	return predictPoint;
}