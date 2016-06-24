
#ifndef OPTION_JOUEUR_HH
#define OPTION_JOUEUR_HH

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
#include "AMenu.hh"
#include "Name.hh"
#include "Core.hpp"

class OptionJoueur : public AMenu
{
public:
	OptionJoueur(gdl::SdlContext &context, gdl::BasicShader &shader,
		gdl::Input &input, gdl::Texture &font);
	OptionJoueur(gdl::SdlContext &context, gdl::BasicShader &shader,
		gdl::Input &input, Core &core);

	bool initialize();
	bool update();

	void changeJoueurMode();

	virtual ~OptionJoueur();

private:
	gdl::Input &input;
	int nbJoueurs;
	Name nameJoueur1;
	Name nameJoueur2;
  Core &core;
};

#endif
