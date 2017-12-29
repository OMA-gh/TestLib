#include "Texture.h"

#define TEXTURE_DIR "Resources/"

Texture::Texture() {
	mpHtMap = nullptr;
}
Texture::~Texture() {
	delete mpHtMap;
}

void Texture::init(const std::string& file_name) {
	mFileName = TEXTURE_DIR + file_name;
	mpHtMap = SOIL_load_image(
		mFileName.c_str(),
		&mWidth, &mHeight, &mChannel, 0);
	if (!mpHtMap) {
		printf("texture load error:%s\n", file_name.c_str());
	}
}