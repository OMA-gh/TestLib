#include "ActorMgr.h"
#include "../Actor/Test.h"

ActorMgr *ActorMgr::s_pInstance = nullptr;

ActorMgr::ActorMgr() {
};
ActorMgr::~ActorMgr() {
    Clear();
};

void ActorMgr::update() {
    auto end = mActorPtrArray.end();
    for (auto it = mActorPtrArray.begin(); it != end; it++) {
        (*it).second->update();
    }
}

bool ActorMgr::addActor(std::string actor_name, std::unique_ptr<Actor> actor, Model* model) {
    actor->setModel(model);
    actor->setName(actor_name);
    mActorPtrArray[actor_name] = std::move(actor);

    return true;
}

Actor* ActorMgr::getActorPtr(std::string actor_name) {
    auto find = mActorPtrArray.find(actor_name);
    if (find == mActorPtrArray.end()) {
        printf("ERROR:actor is not exist [actor name:%s] @ActorMgr::getActorPtr()", actor_name.c_str());
        return nullptr;
    }
    else {
        return find->second.get();
    }
}

bool ActorMgr::Clear() {
    auto end = mActorPtrArray.end();
    for (auto it = mActorPtrArray.begin(); it != end; it++) {
        (*it).second.reset();
    }
    mActorPtrArray.clear();
    return true;
}