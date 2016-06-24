#pragma once

#include <OpenGL.hh>
#include <Game.hh>
#include <Input.hh>
#include <SdlContext.hh>
#include <Model.hh>
#include <iostream>
#include <BasicShader.hh>
#include <Texture.hh>
#include <Geometry.hh>
#include "Core.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "image.hh"
#include "AMenu.hh"
#include "Name.hh"

class ChargerPartie : public AMenu
{
public:
	ChargerPartie(gdl::SdlContext &context, gdl::BasicShader &shader,
		gdl::Input &input, Core &core);

	bool initialize();
	bool update();

	virtual ~ChargerPartie();

private:
	gdl::Input &input;
	Name save;
  Core &core;
};

