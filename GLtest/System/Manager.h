#pragma once

#define GET_INSTANCE(...) __VA_ARGS__::GetInstance()

#include "Singleton.h"
#include "TextureMgr.h"
#include "ActorMgr.h"
#include "ModelMgr.h"
#include "Render.h"
#include "Physics.h"
#include "../Camera.h"
