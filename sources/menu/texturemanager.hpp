#pragma once

#include <map>
#include "AMenu.hh"
#include "image.hh"

class TextureManager {

  public:
    static TextureManager &Instance();

    Image *getImageByName(AMenu::TextureName name);
    gdl::Texture *getFont();
    void loadTextures();

  private:
    static TextureManager m_instance;

    TextureManager (const TextureManager&) {}
    TextureManager();
    ~TextureManager();

    std::map<AMenu::TextureName, Image*> imageMap;
    gdl::Texture *font;

};

