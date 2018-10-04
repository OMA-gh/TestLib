
#include "Cube.h"

Cube::Cube() : Model() {
	mTextureName = "test.jpg";
}

void Cube::setIndexInfo() {
    float side = 2.0f;
    float side2 = side / 2.0f;

    float v[24 * 3] = {
        // Front
        -side2, -side2, side2,
        side2, -side2, side2,
        side2,  side2, side2,
        -side2,  side2, side2,
        // Right
        side2, -side2, side2,
        side2, -side2, -side2,
        side2,  side2, -side2,
        side2,  side2, side2,
        // Back
        -side2, -side2, -side2,
        -side2,  side2, -side2,
        side2,  side2, -side2,
        side2, -side2, -side2,
        // Left
        -side2, -side2, side2,
        -side2,  side2, side2,
        -side2,  side2, -side2,
        -side2, -side2, -side2,
        // Bottom
        -side2, -side2, side2,
        -side2, -side2, -side2,
        side2, -side2, -side2,
        side2, -side2, side2,
        // Top
        -side2,  side2, side2,
        side2,  side2, side2,
        side2,  side2, -side2,
        -side2,  side2, -side2
    };

    float n[24 * 3] = {
        // Front
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        // Right
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        // Back
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        // Left
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        // Bottom
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        // Top
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    float tex[24 * 2] = {
        // Front
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Right
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Back
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Left
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Bottom
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Top
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

	for (int k = 0; k < 6; k++) {
		for (int i = 0; i < 4; i++) {
            {
                glm::vec3 push_pos(
                    v[12 * k + 3 * i],
                    v[12 * k + 3 * i + 1],
                    v[12 * k + 3 * i + 2]
                );
                mPositionArray.push_back(push_pos);
            }
            {
                glm::vec3 push_normal(
                    n[12 * k + 3 * i],
                    n[12 * k + 3 * i + 1],
                    n[12 * k + 3 * i + 2]
                );
                mNormalArray.push_back(push_normal);
            }
            {
                glm::vec2 push_tex(
                    tex[8 * k + 2 * i],
                    tex[8 * k + 2 * i + 1]
                );
                mTexCoordArray.push_back(push_tex);
            } 
            {
                glm::vec3 push_color(
                    0.3f + 0.05f*k,
                    0.4f + i * 0.1f,
                    1 - i * 0.1f
                );
                mColorArray.push_back(push_color);
            }
		}
	}
    int push_index_array[36] = {
        0,1,2,
        0,2,3,
        4,5,6,
        4,6,7,
        8,9,10,
        8,10,11,
        12,13,14,
        12,14,15,
        16,17,18,
        16,18,19,
        20,21,22,
        20,22,23
    };

	for (int i = 0; i < 36; i++) {
		mIndexArray.push_back(push_index_array[i]);
	}
}

void Cube::update() {
}

