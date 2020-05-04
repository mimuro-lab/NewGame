
/*!
@file AnimationMove.cpp
@brief AnimationMoveクラス内のメンバ類の定義を行うCPPファイル。
@date 2020/05/04/14:38
@author mimuro
*/

#include "AnimationMove.h"

/*!
@brief Status型の現在現在の状態を入力し、次のコマの座標位置を更新しを返す。
@date 2020/05/04/14:38
@author mimuro
*/
Status AnimationMove::update(
	Status nowStatus, 
	rollAction_Basic nowAction, 
	shared_ptr<CollisionDetect> _collision, 
	shared_ptr<Stage> _stage, 
	shared_ptr<Animation> _animation
)
{
	Status _nextStatus = nowStatus;

	// クラス内変数のnowPointを更新
	nowPoint.x = nowStatus._x;
	nowPoint.y = nowStatus._y;

	// Pysicalクラスにより、現在の状態から現在の速度を計算する。
	nowVelocity = pysical.update(nowAction, nowStatus.directRight);
	nowVelocity = pysical.resetVelocity(nowVelocity, _collision);

	// PredictPointクラスにより、その速度の座標位置が妥当であるか判断し、妥当な座標位置を計算する。
	nextPoint = predictPoint.update(nowPoint ,nowVelocity, _collision, _stage);

	// nextPointをStatus型変数の座標位置に代入し、返す。
	_nextStatus._x = nextPoint.x;
	_nextStatus._y = nextPoint.y;

	return _nextStatus;
	
}