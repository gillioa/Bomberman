#ifndef AMENU_HH
#define AMENU_HH

#include <OpenGL.hh>
#include <Game.hh>
#include <Input.hh>
#include <SdlContext.hh>
#include <Model.hh>
#include <iostream>
#include <BasicShader.hh>
#include <Texture.hh>
#include <Geometry.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "image.hh"
#include "text.hh"

class AMenu : gdl::Game{

public:

	AMenu(gdl::SdlContext &context);
	AMenu(gdl::SdlContext &context, gdl::BasicShader &shader);

	enum TextureName{
	  BACKGROUND,
		OPTION_JOUEUR,
		OPTION_PARTIE,
		SCORES,
		CURSOR,
		TEMP,
		MODE,
		NAME1,
		NAME2,
    MAP,
    NB_IA,
    DEN,
    LOAD,
    PLAY,
    LOAD_NAME,
    TITLE,
    TMP,
    FONT,
    CONTINUER,
    QUITTER,
    SAUVEGARDER,
    IA_LEVEL,
	};

	virtual bool initialize() = 0;
	virtual bool update() = 0;

	virtual void draw();

	void changeCursorPosition(gdl::Input &input);

	virtual ~AMenu();

protected:
	gdl::SdlContext &context;
	gdl::Texture *font;

	std::map<TextureName, Image*> fixed;
	std::map<TextureName, Text> textes;

	std::list<int> cursorPositions;
	std::list<int>::iterator cursorPosition;

	gdl::BasicShader shader;

};

#endif
