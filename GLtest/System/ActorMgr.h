#pragma once

#include <vector>
#include <unordered_map>
#include <memory>

#include "Singleton.h"

// Actors
#include "../Actor/Actor.h"

class ActorMgr : public Singleton<ActorMgr> {
public:
    friend class Singleton<ActorMgr>;//Singletonでのインスタンス作成は許可

public:
    ActorMgr();
    ~ActorMgr();

    void update();
    bool requestCreateActor(std::string actor_name, Model* model);
    Actor* getActorPtr(std::string actor_name);
    bool Clear();

private:
    std::unordered_map<std::string, std::unique_ptr<Actor>> mActorPtrArray;
};