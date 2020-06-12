#include "PredictStageShift.h"

Dimention PredictStageShift::update(shared_ptr<Stage> stage, shared_ptr<Player> player, Dimention shiftinStage)
{
	Dimention fixedShiftingStage = shiftinStage;
	
	//�Ƃ肠�����A�v���C���[�̒�݂̂𒲂ׂ�(2020/06/13)
	int playerBottom = player->getStatus()._y + player->getToBottom();
	int predictBottom = playerBottom - shiftinStage.y;

	

	int deffOfPredictBottomAndBlockHead = 0;
	

	// �����̒�𒲂ׂ�
	DrawCircle(player->getStatus()._x, predictBottom, 3, GetColor(0, 255, 0), false);
	if (IsDetectedStage(player->getStatus()._x, predictBottom - 1, stage)) {
		int blockHead = stage->getBlockCell(player->getStatus()._x, predictBottom).y1 + stage->getPointLeftUpY();
		deffOfPredictBottomAndBlockHead = playerBottom - blockHead;
		fixedShiftingStage.y -= deffOfPredictBottomAndBlockHead;
		DrawCircle(player->getStatus()._x, predictBottom, 3, GetColor(0, 255, 0), true);
		printfDx("fixed\n");
	}

	// �E�̒�𒲂ׂ�
	DrawCircle(player->getStatus()._x + player->getToRight() - 1, predictBottom, 3, GetColor(0, 255, 0), false);
	if (IsDetectedStage(player->getStatus()._x + player->getToRight() - 1, predictBottom - 1, stage)) {
		int blockHead = stage->getBlockCell(player->getStatus()._x, predictBottom).y1 + stage->getPointLeftUpY();
		deffOfPredictBottomAndBlockHead = playerBottom - blockHead;
		fixedShiftingStage.y -= deffOfPredictBottomAndBlockHead;
		DrawCircle(player->getStatus()._x + player->getToRight() -1, predictBottom, 3, GetColor(0, 255, 0), true);
		printfDx("fixed\n");
	}

	// ���̒�𒲂ׂ�
	DrawCircle(player->getStatus()._x - player->getToLeft(), predictBottom, 3, GetColor(0, 255, 0), false);
	if (IsDetectedStage(player->getStatus()._x - player->getToLeft(), predictBottom - 1, stage)) {
		int blockHead = stage->getBlockCell(player->getStatus()._x, predictBottom).y1 + stage->getPointLeftUpY();
		deffOfPredictBottomAndBlockHead = playerBottom - blockHead;
		fixedShiftingStage.y -= deffOfPredictBottomAndBlockHead;
		DrawCircle(player->getStatus()._x - player->getToLeft(), predictBottom, 3, GetColor(0, 255, 0), true);
		printfDx("fixed\n");
	}

	return fixedShiftingStage;

}

bool PredictStageShift::IsDetectedStage(int x, int y, shared_ptr<Stage> stage)
{
	// x, y���W���X�e�[�W�̂ǂ̃C���f�b�N�X�ɒl���邩�H
	unsigned char _CellXNum = (x - stage->getPointLeftUpX()) / stage->getBlockWidth() - stage->getAbsIndInitDrawingLeftUpX();
	unsigned char _CellYNum = (y - stage->getPointLeftUpY()) / stage->getBlockHeight() - stage->getAbsIndInitDrawingLeftUpY();

	//�X�e�[�W�䂩��͂ݏo��Ȃ�ǂɏՓ˂����Ƃ������ƁB
	if (_CellXNum < 0 || _CellYNum < 0 || _CellXNum >= stage->getBlockXNum() || _CellYNum >= stage->getBlockYNum()) {
		return false;
	}

	// �����Ax, y�ɂ���X�e�[�W�̗v�f��block��������Փ˂Ɣ���B
	if (stage->getStage()[_CellXNum][_CellYNum]._status == Define::BlockCell::cellStatus::block) {
		return true;
	}

	// �ǂ��ɂ��Փ˂��Ȃ����false��Ԃ��B
	return false;
}