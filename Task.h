#pragma once

class Task {
public:
    virtual ~Task() {}
    //! �����������͎������Ă����Ȃ��Ă�����
    virtual void initialize() {}     
    //! �I�������͎������Ă����Ȃ��Ă�����
    virtual void finalize() {}     
    //! �X�V�����͕K���p����Ŏ�������
    virtual void update() = 0;   
    //! �`�揈���͕K���p����Ŏ�������
    virtual void draw() = 0;   
};