#pragma once

//template <typename _T>
// �񕪖؂̃m�[�h
struct Node
{
    int    value;     // �l
    Node* pNext[2];  // �q�m�[�h
};

// �񕪖�
struct Tree
{
    int    value;  // �l
    Node* pRoot;  // ���[�g
};