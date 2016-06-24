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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "image.hh"
#include "AMenu.hh"
#include "Name.hh"
#include "Core.hpp"

class OptionPartie : public AMenu
{
public:
	OptionPartie(gdl::SdlContext &context, gdl::BasicShader &shader,
		gdl::Input &input, Core &core);

	bool initialize();
	bool update();


  void updateDensite();
  void updateNbIA();
  void updateTemps();
  void changeIALevel();
  void changeMap();
  void updateMaxIaWhenMapChanged();

	virtual ~OptionPartie();

private:
	gdl::Input &input;
  int densit;
  int nbIA;
  int temps;
  Core &core;
  int iaLevel;
  int maxNbIa;
  std::vector<std::string> levels;

  int noMap;
  std::vector<std::string> maps;
};

