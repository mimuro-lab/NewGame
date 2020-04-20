#include "Gamepad.h"
#include <DxLib.h>
#include "Keyboard.h"
#include "Define.h"
#include <string>
#include <algorithm>

using namespace std;

Gamepad::Gamepad()
{
    _idArray[ePad::down] = 0;
    _idArray[ePad::left] = 1;
    _idArray[ePad::right] = 2;
    _idArray[ePad::up] = 3;
    _idArray[ePad::maru] = 5;
    _idArray[ePad::sankaku] = 4;
    _idArray[ePad::sikaku] = 7;
    _idArray[ePad::batu] = 6;
    _idArray[ePad::select] = 13;
    _idArray[ePad::start] = 12;
}

void Gamepad::update()
{
    int padInput;
    padInput = GetJoypadInputState(DX_INPUT_PAD1);//�p�b�h�̓��͏�Ԃ��擾
    for (int i = 0; i < 16; i++) {
        if (padInput & (1 << i)) {
            _pad[i]++;
        }
        else {
            _pad[i] = 0;
        }
    }
    printfDx("\n");
}

/*!
@brief �n���ꂽ�p�b�h�L�[�ԍ��̓��̓t���[������Ԃ�
*/
int Gamepad::get(ePad eID) const
{
    return _pad[_idArray[eID]];
}