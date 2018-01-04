#pragma once

#include "Actor.h"

class Light : public Actor {
public:
    Light();
    virtual void update() override;
private:
};