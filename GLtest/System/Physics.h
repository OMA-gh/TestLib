#pragma once

#include "Singleton.h"

class Physics : public Singleton<Physics> {
public:
    friend class Singleton<Physics>;//Singleton�ł̃C���X�^���X�쐬�͋���

public:
    Physics();
    ~Physics();
};