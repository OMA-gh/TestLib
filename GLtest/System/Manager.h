#pragma once

#define GET_INSTANCE(...) __VA_ARGS__::GetInstance()

#include "Singleton.h"
#include "TextureMgr.h"
#include "ActorMgr.h"
#include "Render.h"
#include "../Camera.h"
/*
template<typename T>
void createInstance<T>() {
    T::Create();
}

template<typename T>
void destroyInstance<T>() {
    T::Destroy();
}
*/