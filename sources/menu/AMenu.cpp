#include "AMenu.hh"
#include "text.hh"
#include "texturemanager.hpp"

AMenu::~AMenu(){
}

void AMenu::draw(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);



  for (auto &it : this->fixed){
    it.second->draw(this->shader);
	}


	for (auto &it : this->textes) {
		it.second.draw(this->shader, glm::vec3(1.5, 3.0, 1.0));
	}


	this->context.flush();
}


void AMenu::changeCursorPosition(gdl::Input &input)
{
	if (input.getKey(SDLK_UP, true)) {
		if (this->cursorPosition == this->cursorPositions.begin()) {
			this->cursorPosition = this->cursorPositions.end();
		}

		--this->cursorPosition;

		this->fixed[CURSOR]->reset();
		this->fixed[CURSOR]->constructFor2d(150, *(this->cursorPosition));
	}

	if(input.getKey(SDLK_DOWN, true)) {
		++cursorPosition;

		if (this->cursorPosition == this->cursorPositions.end()) {
			this->cursorPosition = this->cursorPositions.begin();
		}

		this->fixed[CURSOR]->reset();
		this->fixed[CURSOR]->constructFor2d(150, *(this->cursorPosition));
	}

}

AMenu::AMenu(gdl::SdlContext &context) :
context(context){
}

AMenu::AMenu(gdl::SdlContext &context, gdl::BasicShader &shader) :
context(context),
shader(shader){
}

