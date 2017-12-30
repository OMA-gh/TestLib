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
    Singleton() {};//外部でのインスタンス作成は禁止
    virtual ~Singleton() {};

private:
    void operator=(const Singleton& obj) {}//代入禁止
    Singleton(const Singleton &obj) {}//コピーコンストラクタ禁止

};
