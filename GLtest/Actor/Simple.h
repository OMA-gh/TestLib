#pragma once

#include "Actor.h"

class Simple : public Actor {
public:
    Simple();

    virtual void prepare() override;
    virtual void update() override;
    virtual void reflectBody() override;
private:
};
#pragma once
