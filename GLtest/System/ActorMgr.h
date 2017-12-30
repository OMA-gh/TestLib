#pragma once

#include <vector>
#include <unordered_map>
#include <memory>

#include "Singleton.h"

// Actors
#include "../Actor/Actor.h"

class ActorMgr : public Singleton<ActorMgr> {
public:
    friend class Singleton<ActorMgr>;//Singleton�ł̃C���X�^���X�쐬�͋���

public:
    ActorMgr();
    ~ActorMgr();

    void update();
    bool AddActor(std::unique_ptr<Actor>& actor);
    bool Clear();

private:
    std::vector<std::unique_ptr<Actor>> mActorPtrArray;
};