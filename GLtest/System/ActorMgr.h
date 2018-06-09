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

    void calc();
    void postCalc();
    bool addActor(std::string actor_name, std::unique_ptr<Actor> actor, Model* model);
    bool addActorDynamic(std::string actor_name, std::unique_ptr<Actor> actor, Model* model);
    Actor* getActorPtr(std::string actor_name);
    const std::unordered_map<std::string, std::unique_ptr<Actor>>& getActorArray() const {
        return mActorPtrArray;
    }
    bool Clear();

private:
    std::unordered_map<std::string, std::unique_ptr<Actor>> mActorPtrArray;
    std::unordered_map<std::string, std::unique_ptr<Actor>> mAddRequestPtrArray;
};