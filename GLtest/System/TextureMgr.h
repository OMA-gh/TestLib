#pragma once

#include "../Model/Texture.h"
#include <vector>
#include <unordered_map>
#include <memory>


class TextureMgr {
public:
    TextureMgr();
    ~TextureMgr();

    Texture* load(std::string filename);
    Texture* getTexture(std::string filename);
private:
    std::unordered_map<std::string, std::unique_ptr<Texture>> mTexturePtrTable;
};