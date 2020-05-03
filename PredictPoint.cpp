#include "PredictPoint.h"

Dimention PredictPoint::calcPredictPoint(Dimention nowPoint, Dimention nowVelocity)
{
	Dimention returnPoint = nowPoint;

	returnPoint.x += nowVelocity.x;
	returnPoint.y += nowVelocity.y;

	return returnPoint;

}

int PredictPoint::fittingPointHorizon(Dimention nowPoint, int predictRange, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage)
{
	// predictRangeが現在位置より右だったら
	if (predictRange > 0) {
		// predictRange分右にブロックがあるかどうか？
		bool isCollisionedPredictRight = _collision->calcShitingCollisionedSideHorizon(CollisionDetect::toShiftDirect::right, predictRange);
		if (isCollisionedPredictRight) {
			// もしあったら、右のブロック左辺に合わせる。（中心座標を返すので、getRange分引く）
			return getForwardBlockNearSideHorizon(nowPoint, predictRange, _collision, _stage) - _collision->getRange(CollisionDetect::toShiftDirect::right);
		}
	}

	// predictRangeが現在位置より左だったら
	if (predictRange < 0) {
		bool isCollisionedPredictLeft = _collision->calcShitingCollisionedSideHorizon(CollisionDetect::toShiftDirect::left, predictRange);
		if (isCollisionedPredictLeft) {
			// もしあったら、左のブロック右辺に合わせる。（中心座標を返すので、getRange分足す）
			return getForwardBlockNearSideHorizon(nowPoint, predictRange, _collision, _stage) + _collision->getRange(CollisionDetect::toShiftDirect::left);
		}
	}
	// もし、右が壁にぶつかっていて、右を調べるようだったら、座標を変えない。
	if (_collision->getCollisionedSide().right && predictRange > 0)
		return nowPoint.x;

	// もし、左が壁にぶつかっていて、左を調べるようだったら、座標を変えない。
	if (_collision->getCollisionedSide().left && predictRange < 0)
		return nowPoint.x;
	// 以上の条件に当てはまらなかったらpredictRangeに移動してもよい。
	return nowPoint.x + predictRange;
}

int PredictPoint::fittingPointVertical(Dimention nowPoint, int predictRange, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage)
{

	// もし、下が壁にぶつかっていて、下を調べるようだったら、座標を変えない。
	if(_collision->getCollisionedSide().bottom && predictRange > 0)
		return nowPoint.y;

	// もし、上が壁にぶつかっていて、上を調べるようだったら、座標を変えない。
	if (_collision->getCollisionedSide().head && predictRange < 0)
		return nowPoint.y;

	// predictYが現在位置より下だったら
	if (predictRange > 0) {
		// predictRange分下にブロックがあるかどうか？
		bool isCollisionedPredictBottom = _collision->calcShitingCollisionedSideVertical(CollisionDetect::toShiftDirect::bottom, predictRange);
		if (isCollisionedPredictBottom) {
			// もしあったら、下のブロック上辺に合わせる。（中心座標を返すので、getRange分引く）
			return getForwardBlockNearSideVertical(nowPoint, predictRange, _collision, _stage) - _collision->getRange(CollisionDetect::toShiftDirect::bottom);
		}
	}

	// predictYが現在位置より上だったら
	if (predictRange < 0) {
		bool isCollisionedPredictHead = _collision->calcShitingCollisionedSideVertical(CollisionDetect::toShiftDirect::head, predictRange);
		if (isCollisionedPredictHead) {
			// もしあったら、上のブロック下辺に合わせる。（中心座標を返すので、getRange分足す）
			return getForwardBlockNearSideVertical(nowPoint, predictRange, _collision, _stage) + _collision->getRange(CollisionDetect::toShiftDirect::head);
		}
	}

	// 以上の条件に当てはまらなかったらpredictRangeに移動してもよい。
	return nowPoint.y + predictRange;
}


int PredictPoint::getForwardBlockNearSideVertical(
	Dimention nowPoint,
	int predictRange,
	std::shared_ptr<CollisionDetect> _collision,
	std::shared_ptr<Stage> _stage
)
{
	// predictRangeが下向きだったら
	if (predictRange > 0)
	{
		// 足元＋predictRangeの座標を計算
		int x = nowPoint.x;
		int y = nowPoint.y + _collision->getRange(CollisionDetect::toShiftDirect::bottom) + Define::blockHeight;
		// その座標にあるブロックの上辺のｙ座標を返す。（中心座標を返すので、getRange分引く）
		return _stage->getBlockCell(x, y).y1;
	}
	// predictRangeが上向きだったら
	if (predictRange < 0) {
		// 頭上＋predictRangeの座標を計算
		int x = nowPoint.x;
		int y = nowPoint.y - _collision->getRange(CollisionDetect::toShiftDirect::head) - Define::blockHeight;
		// その座標にあるブロックの下辺のｙ座標を返す。
		return _stage->getBlockCell(x, y).y2;
	}
	// predictRangeが0だったら同じ座標を返す。

	return nowPoint.y;
}


int PredictPoint::getForwardBlockNearSideHorizon(
	Dimention nowPoint,
	int predictRange,
	std::shared_ptr<CollisionDetect> _collision,
	std::shared_ptr<Stage> _stage
)
{
	// predictRangeが右向きだったら
	if (predictRange > 0)
	{
		// 右側辺＋predictRangeの座標を計算
		int x = nowPoint.x + _collision->getRange(CollisionDetect::toShiftDirect::right) + predictRange;
		int y = nowPoint.y;
		// その座標にあるブロックの左辺のx座標を返す。
		return _stage->getBlockCell(x, y).x1;
	}
	// predictRangeが左向きだったら
	if (predictRange < 0) {
		// 左側辺＋predictRange(predictRangeは負)の座標を計算
		int x = nowPoint.x - _collision->getRange(CollisionDetect::toShiftDirect::left) + predictRange;
		int y = nowPoint.y;
		// その座標にあるブロックの右辺のx座標を返す。
		return _stage->getBlockCell(x, y).x2;
	}
	// predictRangeが0だったら同じ座標を返す。

	return nowPoint.y;
}

Dimention PredictPoint::update(Dimention _nowPoint, Dimention nowVelocity, std::shared_ptr<CollisionDetect> _collision, std::shared_ptr<Stage> _stage)
{

	nowPoint = _nowPoint;

	predictPoint.x = fittingPointHorizon(nowPoint, nowVelocity.x, _collision, _stage);

	predictPoint.y = fittingPointVertical(nowPoint, nowVelocity.y, _collision, _stage);

	return predictPoint;
}
