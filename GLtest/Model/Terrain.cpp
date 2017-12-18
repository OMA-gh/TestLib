
#include <stdio.h>
#include "Terrain.h"

int p[512] = { 151,160,137,91,90,15,                 // Hash lookup table as defined by Ken Perlin.  This is a randomly
131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,    // arranged array of all numbers from 0-255 inclusive.
190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};

float fade(float t) { return t * t * t * (t * (t * 6 - 15) + 10); }
int inc(int num) {
	num++;
	return num;
}
float Clamp01(float v) { return (v < 0) ? 0 : (v > 1) ? 1 : v; }
float Lerp(float a, float b, float x) { return a + Clamp01(x) * (b - a); }
float grad(int hash, float x, float y, float z) {
	int h = hash & 15;
	float u = h < 8 /* 0b1000 */ ? x : y;
	float v;
	if (h < 4 /* 0b0100 */)	v = y;
	else if (h == 12 /* 0b1100 */ || h == 14 /* 0b1110*/) v = x;
	else v = z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}
float grad(int hash, float x, float y) { return ((hash & 1) == 0 ? x : -x) + ((hash & 2) == 0 ? y : -y); }
//パーリンノイズ生成器 
float perlin(float x, float y, float z) {
	//ほんとにこれでいいの？
	//repeat?
	int xi = (int)x & 255;
	int yi = (int)y & 255;
	int zi = (int)y & 255;

	//xf ( 0 ~ 1 )
	float xf = x - (int)x;
	float yf = y - (int)y;
	float zf = z - (int)z;

	//後で使うらしい
	float u = fade(xf);
	float v = fade(yf);
	float w = fade(zf);

	int aaa, aba, aab, abb, baa, bba, bab, bbb;
	aaa = p[p[p[xi] + yi] + zi];
	aba = p[p[p[xi] + inc(yi)] + zi];
	aab = p[p[p[xi] + yi] + inc(zi)];
	abb = p[p[p[xi] + inc(yi)] + inc(zi)];
	baa = p[p[p[inc(xi)] + yi] + zi];
	bba = p[p[p[inc(xi)] + inc(yi)] + zi];
	bab = p[p[p[inc(xi)] + yi] + inc(zi)];
	bbb = p[p[p[inc(xi)] + inc(yi)] + inc(zi)];
	float x1, x2, y1, y2;
	x1 = Lerp(grad(aaa, xf, yf, zf),				// The gradient function calculates the dot product between a pseudorandom
		grad(baa, xf - 1, yf, zf),				// gradient vector and the vector from the input coordinate to the 8
		u);										// surrounding points in its unit cube.
	x2 = Lerp(grad(aba, xf, yf - 1, zf),				// This is all then lerped together as a sort of weighted average based on the faded (u,v,w)
		grad(bba, xf - 1, yf - 1, zf),				// values we made earlier.
		u);
	y1 = Lerp(x1, x2, v);

	x1 = Lerp(grad(aab, xf, yf, zf - 1),
		grad(bab, xf - 1, yf, zf - 1),
		u);
	x2 = Lerp(grad(abb, xf, yf - 1, zf - 1),
		grad(bbb, xf - 1, yf - 1, zf - 1),
		u);
	y2 = Lerp(x1, x2, v);

	return (Lerp(y1, y2, w) + 1) * 0.5;
}
float perlin(float x, float y) {

	int xi = (int)x & 255;
	int yi = (int)y & 255;

	float xf = x - (int)x;
	float yf = y - (int)y;

	float u = fade(xf);
	float v = fade(yf);

	int aa, ab, ba, bb;
	aa = p[p[xi] + yi];
	ab = p[p[xi] + inc(yi)];
	ba = p[p[inc(xi)] + yi];
	bb = p[p[inc(xi)] + inc(yi)];
	float x1, x2;
	x1 = Lerp(grad(aa, xf, yf),
		grad(ab, xf - 1, yf),
		u);
	x2 = Lerp(grad(ba, xf, yf - 1),
		grad(bb, xf - 1, yf - 1),
		u);
	float n = Lerp(x1, x2, v);
	return (n + 1) * 0.5;
}
float OctavePerlin(float x, float y, int octaves, float persistence, float lacunarity) {
	float total = 0;
	float frequency = 1;
	float amplitude = 1;
	float maxValue = 0;

	for (int i = 0; i < octaves; i++) {
		//total += (perlin(x * frequency, y * frequency) * 2 - 1) * amplitude;
		total += (perlin(x * frequency, y * frequency)) * amplitude;
		maxValue += amplitude;
		amplitude *= persistence;
		frequency *= lacunarity;
	}
	return total / maxValue;
}

Terrain::Terrain() : Model(){
}

void Terrain::setIndexInfo() {
    glm::vec3 push_pos(0);
    glm::vec3 push_color(0);
    glm::vec3 push_normal(0);
	for (int i = 0; i < GRID_SIZE; i++) {
		push_pos.x = (float)FIELD_SIZE / SIZE*(i%SIZE);// x
		push_pos.z = (float)FIELD_SIZE / SIZE*((int)(i / SIZE));// z
		float x = push_pos.x / 255.f;
		float z = push_pos.z / 255.f;
		push_pos.y = OctavePerlin(push_pos.x, push_pos.z, 8, 0.8f, 0.4f);// y
		float y = push_pos.y;
		if (y < 0.41) {
			push_color.x = 0.8f;
			push_color.y = 0.5f;
			push_color.z = 0.3f;
		}
		else if (y<0.51) {
			push_color.x = 0.1f;
			push_color.y = 0.8f;
			push_color.z = 0.3f;
		}
		else {
			push_color.x = 0.5f;
			push_color.y = 0.5f;
			push_color.z = 0.5f;
		}
		push_pos.y *= 10.f;// y

		push_normal.x = 0.f;
		push_normal.y = 1.f;
		push_normal.z = 0.f;

        mPositionArray.push_back(push_pos);
        mColorArray.push_back(push_color);
        mNormalArray.push_back(push_normal);
	}
	for (int i = 0; i < SIZE - 1; i++) {
		for (int k = 0; k < SIZE - 1; k++) {
			int index = (i*SIZE + k);
			int index1 = index * 2 * 3;
            mIndexArray.push_back(index);
			mIndexArray.push_back(index + SIZE);
			mIndexArray.push_back(index + 1);

			int index2 = (index * 2 + 1) * 3;
            mIndexArray.push_back(index + SIZE + 1);
			mIndexArray.push_back(index + 1);
			mIndexArray.push_back(index + SIZE);
		}
	}
	for (int i = 1; i < SIZE - 1; i++) {
		for (int k = 1; k < SIZE - 1; k++) {
			glm::vec3 dvec1 = glm::vec3(0.0, 0.0, 0.0);
			glm::vec3 dvec2 = glm::vec3(0.0, 0.0, 0.0);
			glm::vec3 dvec3 = glm::vec3(0.0, 0.0, 0.0);
			int index = (i*SIZE + k);
			int index1 = index;
			glm::vec3 pos = glm::vec3(mPositionArray[index1].x, mPositionArray[index1].y, mPositionArray[index1].z);
			glm::vec3 pos1 = glm::vec3(mPositionArray[index1 - 1].x, mPositionArray[index1 - 1].y, mPositionArray[index1 - 1].z);
			glm::vec3 pos2 = glm::vec3(mPositionArray[index1 + 1].x, mPositionArray[index1 + 1].y, mPositionArray[index1 + 1].z);
			glm::vec3 dvec = pos - pos1;
			dvec = glm::normalize(dvec);
			dvec = glm::cross(dvec, glm::vec3(0, 0, -1));
			if (dvec.y < 0)dvec *= -1;
			dvec1 += glm::normalize(dvec);
			dvec = pos2 - pos;
			dvec = glm::normalize(dvec);
			dvec = glm::cross(dvec, glm::vec3(0, 0, -1));
			if (dvec.y < 0)dvec *= -1;
			dvec1 += glm::normalize(dvec);
			dvec1 = glm::normalize(dvec1);

			int index2 = (index - SIZE);
			pos1 = glm::vec3(mPositionArray[index2].x, mPositionArray[index2].y, mPositionArray[index2].z);
			index2 = (index + SIZE);
			pos2 = glm::vec3(mPositionArray[index2].x, mPositionArray[index2].y, mPositionArray[index2].z);
			dvec = pos - pos1;
			dvec = glm::normalize(dvec);
			dvec = glm::cross(dvec, glm::vec3(1, 0, 0));
			if (dvec.y < 0)dvec *= -1;
			dvec2 += glm::normalize(dvec);
			dvec = pos2 - pos;
			dvec = glm::normalize(dvec);
			dvec = glm::cross(dvec, glm::vec3(1, 0, 0));
			if (dvec.y < 0)dvec *= -1;
			dvec2 += glm::normalize(dvec);
			dvec2 = glm::normalize(dvec2);

			index2 = (index - SIZE) + 1;
			pos1 = glm::vec3(mPositionArray[index2].x, mPositionArray[index2].y, mPositionArray[index2].z);
			index2 = (index + SIZE) - 1;
			pos2 = glm::vec3(mPositionArray[index2].x, mPositionArray[index2].y, mPositionArray[index2].z);
			dvec = pos - pos1;
			dvec = glm::normalize(dvec);
			dvec = glm::cross(dvec, glm::vec3(1, 0, 1));
			if (dvec.y < 0)dvec *= -1;
			dvec3 += glm::normalize(dvec);
			dvec = pos2 - pos;
			dvec = glm::normalize(dvec);
			dvec = glm::cross(dvec, glm::vec3(1, 0, 1));
			if (dvec.y < 0)dvec *= -1;
			dvec3 += glm::normalize(dvec);
			dvec3 = glm::normalize(dvec3);

			glm::vec3 normal = dvec1 + dvec2 + dvec3;
			normal = glm::normalize(normal);
			mNormalArray[index].x = normal.x;
			mNormalArray[index].y = normal.y;
			mNormalArray[index].z = normal.z;
		}
	}
}

