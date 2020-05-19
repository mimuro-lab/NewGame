#pragma once
#include "DxLib.h"
#include "Stage.h"
#include <memory>

using namespace std;

// �G�E�v���C���[�E����������炸�A��ʏ�̃_���[�W�v�f�B
// ����𐶐�����I�u�W�F�N�g�́ADamageObj�Ȃ��Œ�`���ꂽ�����݂̂��w��B
class DamageObj
{

	int damagePointLeftUp_x = 0;
	int damagePointLeftUp_y = 0;

	int x = 0;
	int y = 0;
	int damage = 0;

public:
	DamageObj(int _x, int _y, int _damage) {
		x = _x;
		y = _y;
		damage = _damage;
	}
	~DamageObj() = default;

	void update(int shiftXbyPlyr, int shiftingYbyPlyr);
	void draw() {
		DrawCircle(x + damagePointLeftUp_x, y + damagePointLeftUp_y, 3, GetColor(255, 255, 255), true);
	}

};

