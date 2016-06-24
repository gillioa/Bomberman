#include "MenuScore.hpp"
#include "menuexception.hh"
#include "menuconstantes.hh"
#include "texturemanager.hpp"

MenuScore::MenuScore(gdl::SdlContext &context, gdl::BasicShader &shader, gdl::Input &input) :
  AMenu(context, shader),
  input(input),
  scoresText(50)
{

  this->font = TextureManager::Instance().getFont();

  try {
    this->s.parseFile("scores/scores.cvs");
  } catch (const UnreadableFileException &){
    std::cerr << "Impossible de lire le fichier" << std::endl;
    throw;
  }

  this->fixed[BACKGROUND] = TextureManager::Instance().getImageByName(BACKGROUND);
  this->fixed[TITLE] = TextureManager::Instance().getImageByName(TITLE);


  this->fixed[BACKGROUND]->constructFor2d(0, 0);
  this->fixed[TITLE]->constructFor2d(720, 50);

  unsigned int i = 0;
  unsigned int offset = 0;
  for (auto &it : s.getScores())
  {
    this->scoresText[i].setFont(this->font);
    this->scoresText[i].constructFor2d(it.first, 100, (50 * offset) + 75);
    ++i;
    ++offset;
  }

  offset = 0;
  for (auto &it : s.getScores())
  {
    this->scoresText[i].setFont(this->font);
    this->scoresText[i].constructFor2d(it.second, 700, (50 * offset) + 75);
    ++offset;
    ++i;
  }
}

bool MenuScore::initialize()
{
  return true;
}

bool  MenuScore::update()
{
  this->context.updateInputs(this->input);
  if (this->input.getKey(SDLK_RETURN, true))
    return false;
  return true;
}

void MenuScore::draw()
{
  for (auto &i : this->fixed)
  {
    i.second->draw(this->shader);
  }

  this->context.flush();
}

