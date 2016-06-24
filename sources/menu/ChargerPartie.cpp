#include "ChargerPartie.hh"
#include "myInput.hh"
#include <SDL.h>
#include <algorithm>
#include "menuexception.hh"
#include "menuconstantes.hh"
#include "texturemanager.hpp"

ChargerPartie::ChargerPartie(gdl::SdlContext &context, gdl::BasicShader &shader, gdl::Input &input, Core &core) :
	AMenu(context, shader),
	input(input),
  core(core)
{
}

bool ChargerPartie::initialize()
{

  this->fixed[BACKGROUND] = TextureManager::Instance().getImageByName(BACKGROUND);
  this->fixed[CURSOR] = TextureManager::Instance().getImageByName(CURSOR);
  this->fixed[TITLE] = TextureManager::Instance().getImageByName(TITLE);

  this->font = TextureManager::Instance().getFont();

	this->cursorPositions.push_back(600);

	this->cursorPosition = cursorPositions.begin();

  this->fixed[CURSOR]->constructFor2d(150, *this->cursorPosition);
  this->fixed[TITLE]->constructFor2d(720, 50);
  this->fixed[BACKGROUND]->constructFor2d(0, 0);

  this->textes[LOAD_NAME].setFont(this->font);
	this->textes[LOAD_NAME].constructFor2d("sauvegarde    " + save.toStdString() ,150, 200);
	return true;
}

bool ChargerPartie::update()
{
	this->context.updateInputs(this->input);
	if (this->input.getKey(SDLK_RETURN, true))
  {
    if (this->save.toStrippedStdString().empty())
    {
      core.setIsLoaded(false);
    }
    else
    {
      core.setFileName("sauvegarde/" + this->save.toStrippedStdString() + ".json");
      core.setIsLoaded(true);
    }
		return false;
  }

	if (*this->cursorPosition == 600) {
		char key = myInput::getKey(this->input);

		if (key >= 'a' && key <= 'z') {
			this->textes[LOAD_NAME].reset();
			save.append(key);
      this->textes[LOAD_NAME].constructFor2d("sauvegarde    " + save.toStdString() ,150, 200);
		}

		if (this->input.getKey(SDLK_BACKSPACE, true)) {
      save.deleteLast();
      this->textes[LOAD_NAME].reset();
      this->textes[LOAD_NAME].constructFor2d("sauvegarde    " + save.toStdString(), 150, 200);
		}
	}
	this->changeCursorPosition(this->input);

	return true;
}

ChargerPartie::~ChargerPartie(){
  std::cout << this->save.toStrippedStdString() << std::endl;
}
