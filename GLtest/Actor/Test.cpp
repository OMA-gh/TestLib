#include "Test.h"

Test::Test() : Actor() {

}

void Test::update() {
	//setPosition(getPosition() + glm::vec3(0.f, 0.f, 0.f));
    setPosition(glm::vec3(0.f, 0.f, 0.f));
	//setScale(getScale() + glm::vec3(0.01f, 0.01f, 0.01f));
	setScale(glm::vec3(1.f));
    setRotation(glm::vec3(1.f, 0.f, 0.f));
}