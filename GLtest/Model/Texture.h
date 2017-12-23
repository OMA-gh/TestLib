#pragma once

#include "..\Dependencies\SOIL2\SOIL2.h"

#include <gl/GL/glew.h>
#include <gl/GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <string>

class Texture {
public:
	Texture();
	~Texture();

	void init(const std::string& file_name);

	int getWidth() const {
		return mWidth;
	}
	void setWidth(int width) {
		mWidth = width;
	}
	int getHeight() const {
		return mHeight;
	}
	void setHeight(int height) {
		mHeight = height;
	}
	unsigned char* getImageBitsPtr() {
		return mpHtMap;
	}
	GLuint& getTextureId() {
		return mTid;
	}
private:
	std::string mFileName;
	int mWidth, mHeight;
	int mChannel; 
	unsigned char *mpHtMap;
	GLuint mTid;
};