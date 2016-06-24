#include "ingame.hpp"
#include "OptionJoueur.hh"
#include "OptionPartie.hh"
#include <cstdio>
#include "myInput.hh"
#include "AMenu.hh"
#include "ChargerPartie.hh"
#include "menuexception.hh"
#include "menuconstantes.hh"
#include "scores.hpp"
#include "MenuScore.hpp"
#include "texturemanager.hpp"
#include "Serialize.hpp"

InGame::InGame(gdl::SdlContext &context, gdl::BasicShader &shader, Core &core, gdl::Input &input) :
  AMenu(context, shader),
  core(core),
  input(input)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_DEPTH_TEST);

    glm::mat4 projection;
    projection = glm::ortho(0.0f, 1920.0f, 1080.0f, 0.0f, -1.0f, 1.0f);

    this->shader.bind();
    this->shader.setUniform("view", glm::mat4(1));
    this->shader.setUniform("projection", projection);
}

bool InGame::initialize()
{
  std::stringstream ss;

  ss << this->name.toStdString();

  this->fixed[BACKGROUND] = TextureManager::Instance().getImageByName(BACKGROUND);
  this->fixed[CURSOR] = TextureManager::Instance().getImageByName(CURSOR);
  this->fixed[TITLE] = TextureManager::Instance().getImageByName(TITLE);

  this->font = TextureManager::Instance().getFont();

  this->cursorPositions.push_back(300);
  this->cursorPositions.push_back(450);
  this->cursorPositions.push_back(600);

  this->cursorPosition = this->cursorPositions.begin();

  this->textes[CONTINUER].setFont(this->font);
  this->textes[SAUVEGARDER].setFont(this->font);
  this->textes[QUITTER].setFont(this->font);

  this->fixed[BACKGROUND]->constructFor2d(0, 0);
  this->fixed[CURSOR]->constructFor2d(150, *(this->cursorPosition));
  this->fixed[TITLE]->constructFor2d(720, 50);

  this->textes[CONTINUER].constructFor2d("Continuer la partie", 150, 100);
  this->textes[SAUVEGARDER].constructFor2d("Sauvegarder   " + ss.str(), 150, 150);
  this->textes[QUITTER].constructFor2d("Quitter", 150, 200);

  return true;
}

bool InGame::update()
{
  return false;
}

InGame::ReturnCode InGame::updateCode(){
  std::stringstream ss;

  this->context.updateInputs(this->input);

  if (this->input.getInput(SDLK_RETURN, true))
  {
    if (*cursorPosition == 600)
      return QUITCODE;
    if (*cursorPosition == 300)
      return PLAYCODE;
    if (*cursorPosition == 450)
    {
      Serialize serialize(this->core,  "sauvegarde/" + this->name.toStrippedStdString() + ".json");
    }
  }

  if (this->input.getInput(SDL_QUIT) || this->input.getKey(SDLK_ESCAPE, true))
  {
    return QUITCODE;
  }

  if (*cursorPosition == 450)
  {
    char key = myInput::getKey(this->input);
    if (key >= 'a' && key <= 'z')
    {
      this->name.append(key);

      ss << this->name.toStdString();
      this->textes[SAUVEGARDER].reset();
      this->textes[SAUVEGARDER].constructFor2d("Sauvegarder   " + ss.str(), 150, 150);
    }
    else if (this->input.getKey(SDLK_BACKSPACE, true))
    {
      this->name.deleteLast();
      ss << this->name.toStdString();
      this->textes[SAUVEGARDER].reset();
      this->textes[SAUVEGARDER].constructFor2d("Sauvegarder   " + ss.str(), 150, 150);
    }
  }

  this->changeCursorPosition(this->input);

  return CONTINUECODE;
}

InGame::~InGame()
{
}
