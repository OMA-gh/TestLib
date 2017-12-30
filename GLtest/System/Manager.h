#pragma once

#define GET_INSTANCE(...) __VA_ARGS__::GetInstance()

#include "Singleton.h"
#include "TextureMgr.h"

static void createInstance() {
    TextureMgr::Create();
}

static void destroyInstance() {
    TextureMgr::Destroy();
}