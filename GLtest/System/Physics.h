#pragma once

#include "Singleton.h"

class Physics : public Singleton<Physics> {
public:
    friend class Singleton<Physics>;//Singletonでのインスタンス作成は許可

public:
    Physics();
    ~Physics();
};