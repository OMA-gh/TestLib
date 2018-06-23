#pragma once

#include "Actor.h"

class Test : public Actor {
public:
	Test();

    virtual void prepare() override;
	virtual void update() override;
private:
};