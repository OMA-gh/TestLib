#pragma once

#include <tiny_obj_loader.h>

#include "Model.h"

class ObjModel : public Model {
public:
    ObjModel();
    ~ObjModel() {};

    void update();
private:
    void PrintInfo(const tinyobj::attrib_t& attrib,
        const std::vector<tinyobj::shape_t>& shapes,
        const std::vector<tinyobj::material_t>& materials);
private:
    virtual void setIndexInfo() override;
};