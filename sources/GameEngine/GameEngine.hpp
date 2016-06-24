#ifndef _GAME_ENGINE_HPP_
#define _GAME_ENGINE_HPP_

#include <OpenGL.hh>
#include <Game.hh>
#include <Input.hh>
#include <SdlContext.hh>
#include <BasicShader.hh>
#include <Clock.hh>
#include <Model.hh>
#include <Texture.hh>
#include <Geometry.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Cube.hpp"
#include "Plan.hpp"
#include "Player.hpp"
#include "PlayerGraph.hpp"
#include "menu.hh"
#include "Core.hpp"

#include "Camera.hpp"

typedef unsigned int	Uint;

class	GameEngine;

typedef AObjectGraph *(GameEngine::*Choices)(const AObject *);

class GameEngine : public gdl::Game
{
private:
  std::map<int, Plan *>		playerSpots;
  std::map<bonusType, std::string>		bonusObjects;
  std::map<std::string, AObjectGraph *>		drawObjects;
  std::map<std::string, gdl::Geometry *>	objGeo;
  std::map<std::string, gdl::Texture *>	usableTexts;
  std::map<std::string, MyModel *>	usableModels;
  std::map<objType, Choices>	choose;
  //std::vector<AObjectGraph*>	objects;
  gdl::Clock			*clock;
  gdl::Input			input;
  Plan		*plan;
  PlayerGraph		*player1;
  PlayerGraph		*player2;
  bool			splitScreen;
  Map				*map;
  gdl::BasicShader		&shader;
  gdl::SdlContext		&context;
  Uint			width;
  Uint			height;
private:
  AObjectGraph	*getObjFromWall(const AObject *);
  AObjectGraph	*getObjFromBonus(const AObject *);
  AObjectGraph	*getObjFromBomb(const AObject *);
  AObjectGraph	*getObjFromCase(const Case *);
  std::vector<AObjectGraph *>  getObjectsFromMap(const Player *);
  bool	initTextures();
  bool	initModels();
  bool	initForms(Player *, Player *, std::vector<IA *> ia);
  bool	initObjects();
  void	updateBombs(std::list<t_explod *> &, bool);
  void	affInfos(const PlayerGraph *) const;
  void	drawPlayer(PlayerGraph *);
  template<typename T>
  void	freeMap(T);
public:
  void	disableSplit() const;
  void	getPlayerFromSquare(std::vector<AObjectGraph *> &, Case* , Uint x, Uint y);
  GameEngine(Map *, gdl::SdlContext &context, gdl::BasicShader &shader, Core&, bool split= false);
  bool  pauseAsked();
  virtual ~GameEngine();
  //virtual bool initialize(Player *player1, Player *player2 = 0) {};
  virtual bool initialize(Player *player1, Player *player2, std::vector<IA *> ia);
  virtual bool initialize() {return false;};
  virtual bool update();
  virtual void draw(std::list<t_explod *> &);
  virtual void draw() {};
  Menu::ReturnCode startMenu();
  Core &core;
};

#endif
