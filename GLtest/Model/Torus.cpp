
#include "Torus.h"

Torus::Torus() : Model() {
    mTextureName = "test.jpg";
}

void Torus::setIndexInfo() {
#define PI 3.141592653589793
#define TWOPI 6.2831853071795862

    const int rings = 50;
    const int sides = 50;
    const float outerRadius = 0.7f;
    const float innerRadius = 0.3f;

    const float ringFactor = (float)(TWOPI / (float)rings);
    const float sideFactor = (float)(TWOPI / (float)sides);

    glm::vec3 push_pos(0.f, 0.f, 0.f);
    glm::vec3 push_normal(0.f, 0.f, 0.f);
    glm::vec3 push_color(0.f, 0.f, 0.f);
    glm::vec2 push_texcoord(0.f, 0.f);

    for (int ring = 0; ring <= rings; ring++) {
        float u = ring * ringFactor;
        float cu = cosf(u);
        float su = sinf(u);
        for (int side = 0; side < sides; side++) {
            float v = side * sideFactor;
            float cv = cosf(v);
            float sv = sinf(v);
            float r = (outerRadius + innerRadius * cv);
            push_pos[0] = r * cu;
            push_pos[1] = r * su;
            push_pos[2] = innerRadius * sv;
            push_normal[0] = cv * cu * r;
            push_normal[1] = cv * su * r;
            push_normal[2] = sv * r;
            push_texcoord[0] = (float)(u / TWOPI);
            push_texcoord[1] = (float)(v / TWOPI);
            // Normalize
            float len = sqrt(push_normal[0] * push_normal[0] +
                push_normal[1] * push_normal[1] +
                push_normal[2] * push_normal[2]);
            push_normal[0] /= len;
            push_normal[1] /= len;
            push_normal[2] /= len;

            mPositionArray.push_back(push_pos);
            mNormalArray.push_back(push_normal);
            mColorArray.push_back(push_color);
            mTexCoordArray.push_back(push_texcoord);
        }
    }

    for (int ring = 0; ring < rings; ring++) {
        int ringStart = ring * sides;
        int nextRingStart = (ring + 1) * sides;
        for (int side = 0; side < sides; side++) {
            int nextSide = (side + 1) % sides;
            // The quad
            mIndexArray.push_back(ringStart + side);
            mIndexArray.push_back(nextRingStart + side);
            mIndexArray.push_back(nextRingStart + nextSide);
            mIndexArray.push_back(ringStart + side);
            mIndexArray.push_back(nextRingStart + nextSide);
            mIndexArray.push_back(ringStart + nextSide);
        }
    }

}

void Torus::update() {
    for (int i = 0; i < 8; i++) {
        //mPositionArray[i].z += 0.01;
    }
}

void Torus::render() const {

}

