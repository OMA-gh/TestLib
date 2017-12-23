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
	void forceSetTextureId(GLuint id) {
		mTid = id;
	}
	GLuint getTextureId() const{
		return mTid;
	}
	GLuint* getTextureIdPtr() {
		return &mTid;
	}
	GLuint getColorType() const {
		return mChannel == 4 ? GL_RGBA : GL_RGB;
	}
private:
	std::string mFileName;
	int mWidth, mHeight;
	int mChannel; 
	unsigned char *mpHtMap;
	GLuint mTid;
};