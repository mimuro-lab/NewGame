
/*!
@file Animation.cpp
@brief Animationクラス内のメンバ類の定義を行うCPPファイル。
@date 2020/04/21/9:53
@author mimuro
*/

#include "Animation.h"

/*!
@brief 一回呼び出すごとにアニメーションを１コマ進める。そのコマでのStatusを引数で受け取る。
@par 画像ファイル群imageHandlesを全て表示するか、DrawingIndexEndを超えるまで更新する。
@date 2020/04/21/9:56
@author mimuro
*/
void Animation::update(Define::Status _status)
{
	if (NowDraiwngImageIndex >= imageHandles.size()|| NowDraiwngImageIndex > DrawingIndexEnd) {
		IsEnd = true;
		return;
	}

	status = _status;

	NowDrawingImageHandle = imageHandles[NowDraiwngImageIndex];
	
	DrawingSteps_counter++;
	DrawingSteps_counter %= DrawingSteps;
	
	if(DrawingSteps_counter == 0)
		NowDraiwngImageIndex++;
}

/*!
@brief update関数で決めた描画対象の画像を表示する。IsEndがtrueだと表示をやめる。
@date 2020/04/21/9:57
@author mimuro
*/
void Animation::draw() const
{
	if (IsEnd)
		return;
	DrawRotaGraph2(status._x, status._y, status._x, status._y, 1.0, 0, NowDrawingImageHandle, true, !status.directRight);
}