#pragma once

#include <vector>
#include <unordered_map>
#include <memory>

#include "Singleton.h"

#include "../Model/Model.h"

class ModelMgr : public Singleton<ModelMgr> {
public:
    friend class Singleton<ModelMgr>;//Singletonでのインスタンス作成は許可

public:
    ModelMgr();
    ~ModelMgr();

    void addModel(std::string name, std::unique_ptr<Model> model);
    Model* getModelPtr(std::string actor_name);
    bool Clear();

private:
    std::unordered_map<std::string, std::unique_ptr<Model>> mModelPtrMap;
};