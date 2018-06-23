#include "ActorMgr.h"
#include "../Actor/Test.h"

ActorMgr *ActorMgr::s_pInstance = nullptr;

ActorMgr::ActorMgr() {
};
ActorMgr::~ActorMgr() {
    Clear();
};

void ActorMgr::preCalc() {
    auto end = mAddRequestPtrArray.end();
    for (auto it = mAddRequestPtrArray.begin(); it != end; it++) {
        if (mActorPtrArray[it->first] == nullptr) {
            mActorPtrArray[it->first] = std::move(it->second);
        }
    }
    mAddRequestPtrArray.clear();
}

void ActorMgr::calc() {
    for (auto it = mActorPtrArray.begin(), end = mActorPtrArray.end(); it != end; it++) {
        (*it).second->update();
    }
}

void ActorMgr::postCalc() {
    for (auto it = mActorPtrArray.begin(), end = mActorPtrArray.end(); it != end; it++) {
        (*it).second->reflectBody();
    }
}

bool ActorMgr::addActor(std::string actor_name, std::unique_ptr<Actor> actor, Model* model) {
    if (mAddRequestPtrArray[actor_name] == nullptr) {
        actor->prepare();
        actor->setModel(model);
        actor->setName(actor_name);
        mAddRequestPtrArray[actor_name] = std::move(actor);

        return true;
    }
    else {
        return false;
    }
}

bool ActorMgr::addActorDynamic(std::string actor_name, std::unique_ptr<Actor> actor, Model* model) {
    if(mActorPtrArray[actor_name] == nullptr) {
        actor->prepare();
        actor->setModel(model);
        actor->setName(actor_name);
        mActorPtrArray[actor_name] = std::move(actor);

        return true;
    }
    else {
        return false;
    }
}

const Actor& ActorMgr::getActor(std::string actor_name) {
    auto find = mActorPtrArray.find(actor_name);
    return *find->second.get();
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
    {
        auto end = mActorPtrArray.end();
        for (auto it = mActorPtrArray.begin(); it != end; it++) {
            (*it).second.reset();
        }
        mActorPtrArray.clear();
    }
    {
        auto end = mAddRequestPtrArray.end();
        for (auto it = mAddRequestPtrArray.begin(); it != end; it++) {
            (*it).second.reset();
        }
        mAddRequestPtrArray.clear();
    }
    return true;
}