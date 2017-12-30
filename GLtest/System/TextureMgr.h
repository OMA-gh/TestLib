#pragma once

#include <vector>
#include <unordered_map>
#include <memory>

#include "Singleton.h"
#include "../Model/Texture.h"

class TextureMgr : public Singleton<TextureMgr> {
public:
    friend class Singleton<TextureMgr>;//Singleton�ł̃C���X�^���X�쐬�͋���

public:
    TextureMgr();
    ~TextureMgr();

    Texture* load(std::string filename);
    Texture* getTexture(std::string filename);
private:
    std::unordered_map<std::string, std::unique_ptr<Texture>> mTexturePtrTable;
};