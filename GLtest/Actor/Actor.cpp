#include "Actor.h"


Actor::Actor() 
	: mPosition(0.f)
	, mScale(0.f)
	, mRotation(0.f)
{	
};

void Actor::render() const {
	glPushMatrix();
	glTranslatef(getPosition().x, getPosition().y, getPosition().z);
	mModel->render();
	glPopMatrix();
}