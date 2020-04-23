#pragma once

/*!
@file Define.h
@brief ���낢��Ȓ�`���܂Ƃ܂�ׂ̃w�b�_�t�@�C��
@date 2020/04/15/0:19
@author mimuro
*/

/*!
@enum eScene
@brief �V�[���̒�`�A�N���X���Ɣ��Ȃ��悤�ɃV�[���̓���'e'��t����悤�ɂ���B
@date 2020/04/15/16:47
@author mimuro
*/
enum eScene {
	eNone,
	eStartScene,
	eMenuScene,
	eConfigScene,
	eGameScene,
};

/*!
@class Define
@brief ������p�����[�^�̒�`��ێ�����N���X
@date 2020/04/15/0:19
@author mimuro
*/
class Define final {
public:
	//! �E�B���h�E�T�C�Y��
	const static int WIN_W;

	//! �E�B���h�E�T�C�Y�c
	const static int WIN_H;
	
	//! �~����
	const static float PI;	

	//! �v���C���[��G�̃X�e�[�^�X�Ǘ��̍\����
	struct Status {
		int _x = 0;
		int _y = 0;
		bool directRight = true;
	};
	
	//! �X�e�[�W�̃u���b�N���̃X�e�[�^�X
	struct BlockCell {
		enum cellStatus {
			none, block,
		};
		int x1, y1, x2, y2;
		cellStatus _status;
	};

	//! �v���C���[�I�u�W�F�N�g��G�I�u�W�F�N�g�̊�{�s���̕��ށB
	enum class rollAction_Basic {
		Brake, Crouch, Damage, Idle, Jump_Fall, Jump_Landing, Jump_MidAir, Jump_Up, Fall, Run, Walk, _end
	};

};