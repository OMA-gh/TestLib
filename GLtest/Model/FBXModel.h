#pragma once

#include <tiny_obj_loader.h>

#include "Model.h"

class FBXModel : public Model {
public:
    FBXModel();
    ~FBXModel() {};

    void update();
private:
    virtual void setIndexInfo() override;
};