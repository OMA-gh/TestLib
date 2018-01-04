#include "../System/Manager.h"

#include "Light.h"

Light::Light() : Actor() {
    mIsThroughLight = true;
}

void Light::update() {
    const float PI = 3.141592653589f;
    const float DIST = 100;

    glm::vec3 light_pos;
    const glm::vec3 light_center(10, 0, 10);
    light_pos = light_center + glm::vec3(DIST * cos(PI / 180 * mCount), DIST, DIST * sin(PI / 180 * mCount));
    GET_INSTANCE(ActorMgr)->getActorPtr("Light")->setPosition(light_pos);
    GET_INSTANCE(ActorMgr)->getActorPtr("Light")->setScale(glm::vec3(1.f));
    //mCount++;
    if (mCount > 360) {
        mCount -= 360;
    }
}