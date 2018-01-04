#include "Actor.h"


Actor::Actor() 
	: mPosition(0.f)
	, mScale(0.f)
	, mRotation(0.f)
    , mName("")
    , mCount(0)
    , mIsThroughLight(false)
{	
};

void Actor::render() const {
	mModel->render();
}