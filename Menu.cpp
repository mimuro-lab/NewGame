
/*!
@file Menu.cpp
@brief Menu�N���X���̃����o�ނ̒�`���s��CPP�t�@�C���B
@date 2020/04/16/03:02
@author mimuro
*/

#include "Menu.h"

void Menu::update()
{
	changer->changeScene(eConfig);
}

void Menu::draw()
{
	DrawFormatString(10,10,GetColor(255,255,255), "Menu");
}