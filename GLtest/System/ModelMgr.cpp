#include "ModelMgr.h"
#include "Manager.h"

ModelMgr *ModelMgr::s_pInstance = nullptr;

ModelMgr::ModelMgr() {
};
ModelMgr::~ModelMgr() {
    Clear();
};

void ModelMgr::addModel(std::string name, std::unique_ptr<Model> model) {
    model->init();
    model->setTextureInfo(GET_INSTANCE(TextureMgr)->load(model->getTextureName()));
    mModelPtrMap[name] = std::move(model);
}

Model* ModelMgr::getModelPtr(std::string Model_name) {
    auto find = mModelPtrMap.find(Model_name);
    if (find == mModelPtrMap.end()) {
        printf("ERROR:Model is not exist [Model name:%s] @ModelMgr::getModelPtr()", Model_name.c_str());
        return nullptr;
    }
    else {
        return find->second.get();
    }
}

bool ModelMgr::Clear() {
    auto end = mModelPtrMap.end();
    for (auto it = mModelPtrMap.begin(); it != end; it++) {
        (*it).second.reset();
    }
    mModelPtrMap.clear();
    return true;
}