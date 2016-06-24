#include "menu.hh"
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
#include "LoadSave.hpp"
#include "jsonexception.hpp"

Menu::Menu(gdl::SdlContext &context) :
  AMenu(context),
  core(new Core)
{
  this->ptr[300] = &Menu::startOptionJoueur;
  this->ptr[450] = &Menu::startOptionPartie;
  this->ptr[600] = &Menu::startMenuScore;
  this->ptr[750] = &Menu::startChargerPartie;

  this->core->setSplitScreen(false);
  this->core->setNbIa(0);
  this->core->setDensity(100);
  this->core->setTotalTime(3);

  this->core->setPlayerName(std::string("pl1"), 0);
  this->core->setPlayerName(std::string("pl2"), 1);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


  if ((!this->shader.load("./sources/GDL/shaders/basic.fp", GL_FRAGMENT_SHADER)) ||
      (!this->shader.load("./sources/GDL/shaders/basic.vp", GL_VERTEX_SHADER)) ||
      (!this->shader.build()))
  {
    std::cerr << "Impossible de creer/charger le shader" << std::endl;
  }

  resetCamera();

  try
  {
    TextureManager::Instance().loadTextures();
  }
  catch (const TextureNotFound &e)
  {
    std::cerr << "Impossible de charger toutes les textures ..." << std::endl;
    std::cerr << "Verifier le dossier : " << MenuConstantes::ASSETS_PATH << std::endl;
    throw;
  }

  this->fixed[BACKGROUND] = TextureManager::Instance().getImageByName(BACKGROUND);
  this->fixed[CURSOR] = TextureManager::Instance().getImageByName(CURSOR);
  this->fixed[TITLE] = TextureManager::Instance().getImageByName(TITLE);
  this->font = TextureManager::Instance().getFont();

  this->cursorPositions.push_back(300);
  this->cursorPositions.push_back(450);
  this->cursorPositions.push_back(600);
  this->cursorPositions.push_back(750);
  this->cursorPositions.push_back(900);

  this->cursorPosition = this->cursorPositions.begin();

  this->textes[OPTION_JOUEUR].setFont(this->font);
  this->textes[OPTION_PARTIE].setFont(this->font);
  this->textes[SCORES].setFont(this->font);
  this->textes[LOAD].setFont(this->font);
  this->textes[PLAY].setFont(this->font);

  this->fixed[BACKGROUND]->constructFor2d(0, 0);
  this->fixed[CURSOR]->constructFor2d(150, *(this->cursorPosition));
  this->fixed[TITLE]->constructFor2d(720, 50);

  this->textes[OPTION_JOUEUR].constructFor2d("Option Joueur", 150, 100);
  this->textes[OPTION_PARTIE].constructFor2d("Option Partie", 150, 150);
  this->textes[SCORES].constructFor2d("Scores", 150, 200);
  this->textes[LOAD].constructFor2d("Charger", 150, 250);
  this->textes[PLAY].constructFor2d("Jouer", 150, 300);
}


Menu::Menu(gdl::SdlContext &context, gdl::BasicShader &shader) :
  AMenu(context, shader) {

    this->ptr[300] = &Menu::startOptionJoueur;
    this->ptr[450] = &Menu::startOptionPartie;
    this->ptr[600] = &Menu::startMenuScore;
    this->ptr[750] = &Menu::startChargerPartie;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    resetCamera();

}

void Menu::startMenuScore()
{
  MenuScore menuScore(this->context, this->shader, this->input);

  startSubMenu(menuScore);
}

void Menu::startChargerPartie() {
  ChargerPartie cp(this->context, this->shader, this->input, *this->core);

  startSubMenu(cp);
 }

void Menu::startSubMenu(AMenu &menu)
{
  menu.initialize();

  while (menu.update())
  {
    menu.draw();
  }

  this->fixed[CURSOR]->reset();
  this->fixed[CURSOR]->constructFor2d(150, *(this->cursorPosition));
}

void Menu::startOptionJoueur() {
  OptionJoueur optJoueur(this->context, this->shader, this->input, *this->core);

  startSubMenu(optJoueur);
}

void Menu::startOptionPartie() {
  OptionPartie optPartie(this->context, this->shader, this->input, *this->core);

  startSubMenu(optPartie);
}

bool Menu::initialize()
{
  return true;
}

bool Menu::update() {
  return false;
}

void Menu::resetCamera()
{

  glDisable(GL_DEPTH_TEST);
  glm::mat4 projection;
  projection = glm::ortho(0.0f, 1920.0f, 1080.0f, 0.0f, -1.0f, 1.0f);

  this->shader.bind();
  this->shader.setUniform("view", glm::mat4(1));
  this->shader.setUniform("projection", projection);
}

Menu::ReturnCode Menu::updateCode()
{
  int multiPlace = 3;
  this->context.updateInputs(this->input);

  if (this->input.getInput(SDL_QUIT) || this->input.getKey(SDLK_ESCAPE, true))
  {
    delete this->core;
    return QUITCODE;
  }

  this->changeCursorPosition(this->input);

  if (this->input.getKey(SDLK_RETURN, true)) {
    if (*(this->cursorPosition) == 900) {
      if ((this->core->getNbIa() + 2) < 30)
        multiPlace += 2;
      if ((this->core->getNbIa() + 2) < 10)
        multiPlace += 2;

      if (core->getFileMapName().empty())
      {
        this->mapGen = new RandomMapGenerator();
        this->mapGen->setSizeX((this->core->getNbIa() + 2) * multiPlace);
        this->mapGen->setSizeY((this->core->getNbIa() + 2) * multiPlace);
        this->mapGen->setNbPlayer(this->core->getNbIa() + 2);
        this->mapGen->setFileName("./maps/gen.bomber");
        this->mapGen->GenerateFile();
        this->core->setFileMapName("./maps/gen.bomber");
        delete this->mapGen;
      }

      this->core->setOpt(New);
      this->core->setContext(this->context);
      this->core->setShader(this->shader);

      this->core->run();

      resetCamera();

      delete this->core;
      this->core = new Core;

      this->core->setSplitScreen(false);
      this->core->setNbIa(0);
      this->core->setDensity(100);
      this->core->setTotalTime(3);

      this->core->setPlayerName(std::string("p1"), 0);
      this->core->setPlayerName(std::string("p2"), 1);

      return CONTINUECODE;
    }

    (this->*ptr[*cursorPosition])();
  }

  if (this->core->getIsLoaded())
  {
    try
    {
      LoadSave loadSave(*this->core, this->core->getFileName());
    }
    catch (const UnParsabledException &)
    {
      this->core->setIsLoaded(false);
      return CONTINUECODE;
    }

    this->core->setContext(this->context);
    this->core->setShader(this->shader);

    this->core->run();
    resetCamera();
    delete this->core;
    this->core = new Core();

    this->core->setSplitScreen(false);
    this->core->setNbIa(0);
    this->core->setDensity(100);
    this->core->setTotalTime(3);

    this->core->setPlayerName(std::string("p1"), 0);
    this->core->setPlayerName(std::string("p2"), 1);

    return CONTINUECODE;
  }

  return CONTINUECODE;
}

Menu::~Menu(){
}
