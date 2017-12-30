#include "TextureMgr.h"

TextureMgr *TextureMgr::s_pInstance = nullptr;

TextureMgr::TextureMgr() {
};
TextureMgr::~TextureMgr() {
    auto begin = mTexturePtrTable.begin();
    auto end = mTexturePtrTable.end();
    for (auto it = begin; it != end; it++) {
        it->second.reset();
    }
    mTexturePtrTable.clear();
};

Texture* TextureMgr::load(std::string filename) {
    auto find = mTexturePtrTable.find(filename);
    if (find == mTexturePtrTable.end()) {
        std::unique_ptr<Texture> tex = std::make_unique<Texture>();
        tex->init(filename);
        mTexturePtrTable[filename] = std::move(tex);
        return mTexturePtrTable[filename].get();
    }
    else {
        return find->second.get();
    }
}

Texture* TextureMgr::getTexture(std::string filename) {
    auto find = mTexturePtrTable.find(filename);
    if (find == mTexturePtrTable.end()) {
        printf("ERROR:get texture failed! [filename:%s] @TextureMgr::getTexture()", filename.c_str());
        return nullptr;
    }
    else {
        return find->second.get();
    }
}