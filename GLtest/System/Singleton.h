#pragma once

#include <memory>

template <class T>
class Singleton {
public:
    static T* GetInstance() {
        return s_pInstance;
    }
    static void Create() {
        if (!s_pInstance) {
            s_pInstance = new T;
        }
    };
    static void Destroy() {
        delete s_pInstance;
        s_pInstance = nullptr;
    }

protected:
    static T* s_pInstance;
    Singleton() {};//�O���ł̃C���X�^���X�쐬�͋֎~
    virtual ~Singleton() {};

private:
    void operator=(const Singleton& obj) {}//����֎~
    Singleton(const Singleton &obj) {}//�R�s�[�R���X�g���N�^�֎~

};
