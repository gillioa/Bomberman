#include "OptionPartie.hh"
#include "myInput.hh"
#include <SDL.h>
#include <algorithm>
#include "menuexception.hh"
#include "menuconstantes.hh"
#include "texturemanager.hpp"
#include <sstream>
#include "Except.hpp"

OptionPartie::OptionPartie(gdl::SdlContext &context, gdl::BasicShader &shader, gdl::Input &input, Core &core) :
	AMenu(context, shader),
	input(input),
  densit(core.getDensity()),
  nbIA(core.getNbIa()),
  temps(core.getTotalTime()),
  core(core),
  maxNbIa(core.getMaxIa())

{

  this->iaLevel = core.getLevelIaMenu();
  this->noMap = core.getNoMapForMenu();

  std::stringstream ss;

  this->levels.push_back("easy");
  this->levels.push_back("medium");
  this->levels.push_back("hard");

  this->maps.push_back("Aleatoire");
  this->maps.push_back("map");
  this->maps.push_back("big");
  this->maps.push_back("42");
  this->maps.push_back("plop");

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

  this->fixed[TITLE]->constructFor2d(720, 50);
  this->fixed[BACKGROUND]->constructFor2d(0, 0);
  this->fixed[CURSOR]->constructFor2d(150, *(this->cursorPosition));


  this->textes[TEMP].setFont(this->font);
  this->textes[MAP].setFont(this->font);
  this->textes[NB_IA].setFont(this->font);
  this->textes[DEN].setFont(this->font);
  this->textes[IA_LEVEL].setFont(this->font);

  ss << this->temps;
  this->textes[TEMP].constructFor2d("Temps       " + ss.str() + " min", 150, 100);

  this->textes[MAP].constructFor2d("Map        " + this->maps[this->noMap], 150, 150);

  ss.str("");
  ss.clear();

  ss << this->nbIA;
  this->textes[NB_IA].constructFor2d("Nb IA      " + ss.str(), 150, 200);

  ss.str("");
  ss.clear();

  ss << this->densit;
  this->textes[DEN].constructFor2d("Densite    " + ss.str() + "%", 150, 250);

  this->textes[IA_LEVEL].constructFor2d("Niveau IA  " + this->levels[this->iaLevel], 150, 300);
}

bool OptionPartie::initialize() {
	return true;
}

void OptionPartie::changeIALevel()
{

  if (*cursorPosition != 900)
    return;

  if (this->input.getKey(SDLK_RIGHT, true))
  {
    ++this->iaLevel;
    if (this->iaLevel >= static_cast<int>(this->levels.size()))
      this->iaLevel = 0;
  }

  if (this->input.getKey(SDLK_LEFT, true))
  {
    --this->iaLevel;
    if (this->iaLevel < 0)
      this->iaLevel = this->levels.size() - 1;
  }

  core.setIaDifficulty(this->levels[this->iaLevel]);
  core.setLevelIaMenu(this->iaLevel);

  this->textes[IA_LEVEL].reset();
  this->textes[IA_LEVEL].constructFor2d("Niveau IA  " + this->levels[this->iaLevel], 150, 300);
}

void OptionPartie::updateMaxIaWhenMapChanged()
{
  std::stringstream ss;

  if (this->noMap)
  {
    core.setFileMapName("./maps/" + this->maps[this->noMap] + ".bomber");
    try
    {
      maxNbIa = core.getMaxNbIa("./maps/" + this->maps[this->noMap] + ".bomber");
    } catch (const CorruptedMap &)
    {
      this->noMap++;
      if (this->noMap >= static_cast<int>(this->maps.size()))
        this->noMap = 0;
      this->textes[MAP].reset();
      this->textes[MAP].constructFor2d("Map        " + this->maps[this->noMap], 150, 150);
    }

    this->nbIA = maxNbIa;
    this->core.setMaxIa(maxNbIa);
  }
  else
  {
    this->maxNbIa = 600;
    this->core.setMaxIa(maxNbIa);
    this->nbIA = 0;
    core.setFileMapName("");
  }
  this->core.setNbIa(this->nbIA);
  ss << this->nbIA;
  this->textes[NB_IA].reset();
  this->textes[NB_IA].constructFor2d("Nb IA      " + ss.str(), 150, 200);
}

void OptionPartie::changeMap()
{
  if (*cursorPosition != 450)
    return;

  if (this->input.getKey(SDLK_RIGHT, true))
  {
    ++this->noMap;
    if (this->noMap >= static_cast<int>(this->maps.size()))
      this->noMap = 0;
    updateMaxIaWhenMapChanged();
  }
  if (this->input.getKey(SDLK_LEFT, true))
  {
    --this->noMap;
    if (this->noMap < 0)
      this->noMap = this->maps.size() - 1;
    updateMaxIaWhenMapChanged();
  }

  this->core.setNoMapForMenu(this->noMap);
  this->textes[MAP].reset();
  this->textes[MAP].constructFor2d("Map        " + this->maps[this->noMap], 150, 150);
}

void OptionPartie::updateTemps()
{
  std::stringstream ss;

  ss << this->temps;

  if (*(this->cursorPosition) != 300)
    return;

  if (this->input.getKey(SDLK_RIGHT, true)) {
    ++this->temps;
    if (this->temps > 15) {
      this->temps = 1;
    }
  }

  if (this->input.getKey(SDLK_LEFT, true)) {
    --this->temps;
    if (this->temps < 1) {
      this->temps = 15;
    }
  }
  this->core.setTotalTime(static_cast<unsigned int>(this->temps));
  this->textes[TEMP].reset();
  this->textes[TEMP].constructFor2d("Temps       " + ss.str() + " min", 150, 100);
}


void OptionPartie::updateNbIA()
{
  std::stringstream ss;

  ss << this->nbIA;

  if (*(this->cursorPosition) != 600)
    return;

  if (this->input.getKey(SDLK_RIGHT, true)) {
    ++this->nbIA;
    if (this->nbIA > maxNbIa)
      this->nbIA = 0;
  }

  if (this->input.getKey(SDLK_LEFT, true)) {
    --this->nbIA;
    if (this->nbIA < 0)
      this->nbIA = maxNbIa;
  }


  this->core.setNbIa(this->nbIA);

  this->textes[NB_IA].reset();
  this->textes[NB_IA].constructFor2d("Nb IA      " + ss.str(), 150, 200);
}

void OptionPartie::updateDensite()
{
  std::stringstream ss;

  ss << this->densit;

  if (*(this->cursorPosition) != 750)
  {
    return;
  }

  if (this->input.getKey(SDLK_RIGHT, true))
  {
    ++this->densit;
    if (this->densit > 100)
      this->densit = 0;
  }

  if (this->input.getKey(SDLK_LEFT, true))
  {
    --this->densit;
    if (this->densit < 0)
      this->densit = 100;
  }
  this->core.setDensity(static_cast<Uint>(this->densit));
  this->core.setDensity(static_cast<unsigned int>(this->densit));
  this->textes[DEN].reset();
  this->textes[DEN].constructFor2d("Densite    " + ss.str() + "%", 150, 250);
}

bool OptionPartie::update()
{

	this->context.updateInputs(this->input);

	if (this->input.getKey(SDLK_RETURN, true)) {
		return false;
  }

  this->changeCursorPosition(this->input);
  updateDensite();
  updateNbIA();
  updateTemps();
  changeIALevel();
  changeMap();


  return true;
}


OptionPartie::~OptionPartie()
{
}
