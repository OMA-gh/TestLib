#include "Test.h"

Test::Test() : Actor() {

}

void Test::update() {
	printf("%f,%f,%f\n", getPosition().x, getPosition().y, getPosition().z);
	setPosition(getPosition() + glm::vec3(0.1f, 0.f, 0.f));
}