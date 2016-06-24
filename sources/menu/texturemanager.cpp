#include "texturemanager.hpp"
#include "menuconstantes.hh"
#include "menuexception.hh"
#include <iostream>

TextureManager TextureManager::m_instance = TextureManager();

TextureManager::TextureManager() :
  font(0)
{
}

void TextureManager::loadTextures()
{
  if (this->imageMap.empty())
  {
    this->imageMap[AMenu::BACKGROUND] = new Image(MenuConstantes::ASSETS_PATH + "background.tga");
    this->imageMap[AMenu::CURSOR] = new Image(MenuConstantes::ASSETS_PATH + "cursor.tga");
    this->imageMap[AMenu::TITLE] = new Image(MenuConstantes::ASSETS_PATH + "title.tga");
  }

  if (!this->font)
    {
      this->font = new gdl::Texture();
    if (!this->font->load(MenuConstantes::ASSETS_PATH + "font.tga"))
    {
      throw TextureNotFound();
    }
  }
}

Image *TextureManager::getImageByName(AMenu::TextureName name)
{
  Image *image;

  image = this->imageMap[name];
  image->reset();

  return image;
}

gdl::Texture *TextureManager::getFont()
{
  return this->font;
}

TextureManager::~TextureManager()
{
  delete this->font;
  delete imageMap[AMenu::TITLE];
  delete imageMap[AMenu::BACKGROUND];
  delete imageMap[AMenu::CURSOR];
}

TextureManager &TextureManager::Instance()
{
  return m_instance;
}
