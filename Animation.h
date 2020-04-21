
/*!
@file Animation.h
@brief ImageDraw�N���X����`����Ă���w�b�_�t�@�C��
@date 2020/04/21/9:28
@author mimuro
*/

#pragma once
#include <DxLib.h>
#include <vector>
#include <string>
#include "Define.h"

/*!
@class Animation
@brief �摜���R�}����\�������������Ɏg�p����N���X�BimagePath�ɂ���摜�n���h����vector��n���ƃA�j���[�V�����̊Ǘ����s����B
@date 2020/04/18/23:13
@author mimuro
*/
class Animation
{
	//! �A�j���[�V�������������摜�Q�̉摜�n���h�����i�[����ϐ��B
	std::vector<int> imageHandles;
	//! update(x, y)���Ăяo�������_�̉摜�C���f�b�N�X�B�O����n�܂�B
	char NowDraiwngImageIndex = 0;
	//! update(x, y)���Ăяo�������_�̉摜�n���h���B
	int NowDrawingImageHandle = 0;
	//! �A�j���[�V������r���ŏI���������ɏI���̃C���f�b�N�X������ɐݒ肷��B�ݒ肵���C���f�b�N�X�͕\������Ȃ��B�Q�Ƃ����ꍇ�A�O�E�P�Ԗڂ̂ݕ\���B
	char DrawingIndexEnd = 99;
	//! ��̉摜��\��������X�e�b�v���B��j�U�ɐݒ肷��ƂP�b�ԂɂP�O���̉摜���؂�ւ��B
	char DrawingSteps;
	//! DrawingSteps�𐔂��邽�߂̃J�E���^�[�B
	char DrawingSteps_counter = 0;
	//! �A�j���[�V�������I��������ǂ����B
	bool IsEnd = false;
	//! �A�j���[�V����������ׂ̃X�e�[�^�X�B
	Define::Status status;
public:

	/*!
	@brief �A�j���[�V�������������摜�Q�Ə������W�͕K���󂯎��B����ȊO�͔C�ӁB
	@date 2020/04/21/9:51
	@author mimuro
	*/
	Animation(std::vector<int> _imageHandles, Define::Status _status , char _DrawingSteps = 6, char IndexEnd = 99) :
		imageHandles(_imageHandles)
		, NowDrawingImageHandle(_imageHandles[0])
		, status(_status)
		, DrawingIndexEnd(IndexEnd)
		, DrawingSteps(_DrawingSteps)
	{};
	~Animation() = default;

	//! �X�V������S���֐��B
	void update(Define::Status _status);
	//! �\��������S���֐��B
	void draw() const;
	//! �A�j���[�V�������I��������ǂ������擾����Btrue�Ȃ�I�������B
	const bool isEnd() const { return IsEnd; };

};

