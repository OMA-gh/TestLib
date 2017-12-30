#include "ActorMgr.h"

ActorMgr *ActorMgr::s_pInstance = nullptr;

ActorMgr::ActorMgr() {
};
ActorMgr::~ActorMgr() {
    Clear();
};

void ActorMgr::update() {
    auto end = mActorPtrArray.end();
    for (auto it = mActorPtrArray.begin(); it != end; it++) {
        (*it)->update();
    }
}

bool ActorMgr::AddActor(std::unique_ptr<Actor>& actor) {
    mActorPtrArray.push_back(std::move(actor));
    return true;
}

bool ActorMgr::Clear() {
    auto end = mActorPtrArray.end();
    for (auto it = mActorPtrArray.begin(); it != end; it++) {
        (*it).reset();
    }
    mActorPtrArray.clear();
    return true;
}