#include "OptionJoueur.hh"
#include "myInput.hh"
#include <SDL.h>
#include <algorithm>
#include "menuexception.hh"
#include "menuconstantes.hh"
#include "texturemanager.hpp"

OptionJoueur::OptionJoueur(gdl::SdlContext &context, gdl::BasicShader &shader, gdl::Input &input, Core &core) :
	AMenu(context, shader),
	input(input),
  nameJoueur1(core.getPlayerName(0)),
  nameJoueur2(core.getPlayerName(1)),
  core(core)
{
  nbJoueurs = core.getSplitScreen() ? 2 : 1;
}

void OptionJoueur::changeJoueurMode() {
	if (nbJoueurs == 1) {
		nbJoueurs = 2;
		this->textes[MODE].reset();
		this->textes[MODE].constructFor2d("Mode 2 joueurs", 150, 100);
    this->core.setSplitScreen(true);
	} else {
		nbJoueurs = 1;
		this->textes[MODE].reset();
		this->textes[MODE].constructFor2d("Mode 1 joueur", 150, 100);
    this->core.setSplitScreen(false);
	}
}

bool OptionJoueur::initialize() {


  this->fixed[BACKGROUND] = TextureManager::Instance().getImageByName(BACKGROUND);
  this->fixed[CURSOR] = TextureManager::Instance().getImageByName(CURSOR);
  this->fixed[TITLE] = TextureManager::Instance().getImageByName(TITLE);

  this->font = TextureManager::Instance().getFont();


	this->cursorPositions.push_back(300);
	this->cursorPositions.push_back(450);
	this->cursorPositions.push_back(600);

	this->cursorPosition = cursorPositions.begin();

	this->textes[MODE].setFont(this->font);
	this->textes[NAME1].setFont(this->font);
	this->textes[NAME2].setFont(this->font);

	this->fixed[BACKGROUND]->constructFor2d(0, 0);
	this->fixed[CURSOR]->constructFor2d(150, *this->cursorPosition);
  this->fixed[TITLE]->constructFor2d(720, 50);


  if (nbJoueurs == 1)
		this->textes[MODE].constructFor2d("Mode 1 joueur", 150, 100);
  else
		this->textes[MODE].constructFor2d("Mode 2 joueurs", 150, 100);


	this->textes[NAME1].constructFor2d("Nom joueur 1    " + nameJoueur1.toStdString() ,150, 150);
	this->textes[NAME2].constructFor2d("Nom joueur 2    " + nameJoueur2.toStdString(), 150, 200);

	return true;
}

bool OptionJoueur::update()
{
	this->context.updateInputs(this->input);
	if (this->input.getKey(SDLK_RETURN, true))
  {
    core.setPlayerName(nameJoueur1.toStrippedStdString(), 0);
    core.setPlayerName(nameJoueur2.toStrippedStdString(), 1);
    return false;
  }

	if ((this->input.getKey(SDLK_LEFT, true) || this->input.getKey(SDLK_RIGHT, true)) &&
		*this->cursorPosition == 300) {
		changeJoueurMode();
	}

	if (*this->cursorPosition == 450) {
		char key = myInput::getKey(this->input);
		if (key >= 'a' && key <= 'z') {
			this->textes[NAME1].reset();
			nameJoueur1.append(key);
			this->textes[NAME1].constructFor2d("Nom joueur 1    " + nameJoueur1.toStdString(), 150, 150);
		}

		if (this->input.getKey(SDLK_BACKSPACE, true)) {
				nameJoueur1.deleteLast();
				this->textes[NAME1].reset();
				this->textes[NAME1].constructFor2d("Nom joueur 1    " + nameJoueur1.toStdString(), 150, 150);
		}
	}

	if (*this->cursorPosition == 600) {
		char key = myInput::getKey(this->input);
		if (key >= 'a' && key <= 'z')
    {
			this->textes[NAME2].reset();
			nameJoueur2.append(key);
			this->textes[NAME2].constructFor2d("Nom joueur 2    " + nameJoueur2.toStdString(), 150, 200);
		}

		if (this->input.getKey(SDLK_BACKSPACE, true))
    {
				nameJoueur2.deleteLast();
				this->textes[NAME2].reset();
				this->textes[NAME2].constructFor2d("Nom joueur 2    " + nameJoueur2.toStdString(), 150, 200);
		}
	}

	this->changeCursorPosition(this->input);

	return true;
}


OptionJoueur::~OptionJoueur(){
}
