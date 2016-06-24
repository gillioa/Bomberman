#include "texturemanager.hpp"
#include "AWall.hpp"
#include "Player.hpp"
#include "myModel.hpp"
#include "MapGenerator.hpp"
#include "GameEngine.hpp"
#include "Thread.hpp"
#include "menu.hh"
#include "menuexception.hh"
#include "ingame.hpp"

glm::vec4      getColor(Uint, Uint);

GameEngine::GameEngine(Map *map, gdl::SdlContext &context, gdl::BasicShader &shader, Core &core, bool split) :
  player1(0),
  player2(0),
  splitScreen(split),
  map(map),
  shader(shader),
  context(context),
  width(1920),
  height(1080),
  core(core)
{
  this->bonusObjects[Speed] = "SpeedBonus";
  this->bonusObjects[Range] = "RangeBonus";
  this->bonusObjects[Bombnb] = "BombBonus";
  this->bonusObjects[Hp] = "HpBonus";
  this->bonusObjects[Random] = "RandomBonus";
}

template<typename T>
void	GameEngine::freeMap(T map)
{ 
  typename T::iterator it = map.begin();
  typename T::iterator nextIt = it;
  while (it != map.end())
    {
      ++nextIt;
      delete (*it).second;
      it = nextIt;
    }
}

GameEngine::~GameEngine()
{
  freeMap<std::map<std::string, AObjectGraph *>>(this->drawObjects);
  freeMap<std::map<std::string, gdl::Geometry *>>(this->objGeo);
  freeMap<std::map<std::string, MyModel *>>(this->usableModels);
  freeMap<std::map<std::string, gdl::Texture *>>(this->usableTexts);
  delete this->clock;
  delete this->plan;
  delete this->player1;
  delete this->player2;
}

void	modifVec(glm::vec4 &vec)
{
  if (vec.x < vec.y && vec.x < vec.z)
    vec.x = 0x0;
  else if (vec.y < vec.x && vec.y < vec.z)
    vec.y = 0x0;
  else
    vec.z = 0x0;
}

bool	GameEngine::initForms(Player *p1, Player *p2, std::vector<IA*> ia)
{
  gdl::Geometry	*geo;
  Plan	*plan;
  Uint	i = 0;
  glm::vec4	color;

  this->objGeo["BackGround"] = Plan::createPlan(62.50f, -2.0f, 112.0f);
  this->objGeo["Cube"] = Cube::createCube(1.0f, 0.0f);
  this->objGeo["Explosion"] = Cube::createCube(1.0f, 0.1f);
  this->objGeo["SmallCube"] = Cube::createCube(0.2f, glm::vec4(0x0, 0xFF, 0x0, 0x0));
  this->objGeo["Plan"] = Plan::createPlan(this->map->getWidth(), 0.0f, this->map->getLength(), glm::vec4(0.6f, 0.6f, 0.6f, 0.3f));
  this->objGeo["PlayerSpot"] = Plan::createPlan(1.0f, 0.1f, 1.0f);
  color = getColor(p1->getId(), ia.size() + 2);
  geo = Plan::createPlan(1.0f, 0.1f, 1.0f, color);
  plan = new Plan(1.0f, 1.0f, 1.0f, this->usableTexts["White"]);
  plan->initialize(geo);
  this->playerSpots[p1->getId()] = plan;
  if (p2)
    {
      color = getColor(p2->getId(), ia.size() + 2);
      geo = Plan::createPlan(1.0f, 0.1f, 1.0f, color);
      plan = new Plan(1.0f, 1.0f, 1.0f, this->usableTexts["White"]);
      plan->initialize(geo);
      this->playerSpots[p2->getId()] = plan;
    }
  for (i = 0; i < ia.size(); ++i)
    {
      color = getColor(ia[i]->getPlayer()->getId(), ia.size() + 2);
      geo = Plan::createPlan(1.0f, 0.1f, 1.0f, color);
      plan = new Plan(1.0f, 1.0f, 1.0f, this->usableTexts["White"]);
      plan->initialize(geo);
      this->playerSpots[ia[i]->getPlayer()->getId()] = plan;
    }
  return (true);
}

bool	GameEngine::initModels()
{
  gdl::Model	*model;
  MyModel	*mod;

  if ((model = new gdl::Model) == 0)
    return (false);
  if (model->load("./sources/GDL/assets/marvin.fbx") == false)
    throw (new LoadErr("./sources/GDL/assets/marvin.fbx"));
  model->createSubAnim(0, "Run", 12, 30);
  model->setCurrentSubAnim("Run", true);
  if ((mod = new MyModel(glm::mat4(1), 1, 0.005, model)) == 0)
    return (false);
  this->usableModels["Marvin"] = mod;

  if ((model = new gdl::Model) == 0)
    return (false);
  if (model->load("./sources/GDL/assets/marvin.fbx") == false)
    throw (new LoadErr("./sources/GDL/assets/marvin.fbx"));
  if ((mod = new MyModel(glm::mat4(1), 1, 0.005, model)) == 0)
    return (false);
  this->usableModels["StaticMarvin"] = mod;
  return (true);
}

bool GameEngine::pauseAsked()
{
  if (this->input.getKey(SDLK_ESCAPE, true))
    {
      glViewport(0, 0, this->width, this->height);
      InGame ig(this->context, this->shader, this->core, this->input);

      InGame::ReturnCode code;

      ig.initialize();

      while ((code = ig.updateCode()) == InGame::CONTINUECODE)
	ig.draw();

      if (code == InGame::PLAYCODE)

	{	  glEnable(GL_DEPTH_TEST);
	  this->player1->resetShader(this->shader);
	  if (this->splitScreen)
	    this->player2->resetShader(this->shader);
	  return false;
	}
      
      this->context.updateInputs(this->input);
      
      if (code == InGame::QUITCODE)
	exit(0);
      
      return true;
    }
  return false;
}

bool	GameEngine::initTextures()
{
  gdl::Texture	*text;

  if ((text = new gdl::Texture) == 0)
    return (false);
  if (!text->load("./assets/Floor.tga"))
    throw (new LoadErr("./assets/Floor.tga"));
  this->usableTexts["Floor"] = text;

  if ((text = new gdl::Texture) == 0)
    return (false);
  if (!text->load("./assets/MetalGround.tga"))
    throw (new LoadErr("./assets/MetalGround.tga"));
    //return (false);
  this->usableTexts["Metal"] = text;

  if ((text = new gdl::Texture) == 0)
    return (false);
  if (!text->load("./assets/Tnt.tga"))
    throw (new LoadErr("./assets/Tnt.tga"));
  this->usableTexts["Bomb"] = text;

  if ((text = new gdl::Texture) == 0)
    return (false);
  if (!text->load("./assets/Bonus.tga"))
    throw (new LoadErr("./assets/Bonus.tga"));
  this->usableTexts["RandomBonus"] = text;

  if ((text = new gdl::Texture) == 0)
    return (false);
  if (!text->load("./assets/BoltBox.tga"))
    throw (new LoadErr("./assets/BoltBox.tga"));
  this->usableTexts["Crate"] = text;

  if ((text = new gdl::Texture) == 0)
    return (false);
  if (!text->load("./assets/Crate.tga"))
    throw (new LoadErr("./assets/Crate.tga"));

  this->usableTexts["MetalCrate"] = text;

  if ((text = new gdl::Texture) == 0)
    return (false);
  if (!text->load("./assets/ground.tga"))
    throw (new LoadErr("./assets/ground.tga"));
  this->usableTexts["Rusty"] = text;

  if ((text = new gdl::Texture) == 0)
    return (false);
  if (!text->load("./assets/Explosion.tga"))
    throw (new LoadErr("./assets/Explosion.tga"));
  this->usableTexts["Explosion"] = text;

  if ((text = new gdl::Texture) == 0)
    return (false);
  if (!text->load("./assets/Bonus/Bomberman_Speed.tga"))
    throw (new LoadErr("./assets/Bonus/Bomberman_Speed.tga"));
  this->usableTexts["SpeedBonus"] = text;

  if ((text = new gdl::Texture) == 0)
    return (false);
  if (!text->load("./assets/Bonus/Bomberman_Bombs.tga"))
    throw (new LoadErr("./assets/Bonus/Bomberman_Bombs.tga"));
  this->usableTexts["BombBonus"] = text;

  if ((text = new gdl::Texture) == 0)
    return (false);
  if (!text->load("./assets/White.tga"))
    throw (new LoadErr("./assets/White.tga"));
  this->usableTexts["White"] = text;

  if ((text = new gdl::Texture) == 0)
    return (false);
  if (!text->load("./assets/Bonus/Bomberman_Hp.tga"))
    throw (new LoadErr("./assets/Bonus/Bomberman_Hp.tga"));
  this->usableTexts["HpBonus"] = text;

  if ((text = new gdl::Texture) == 0)
    return (false);
  if (!text->load("./assets/Bonus/Bomberman_Range.tga"))
    throw (new LoadErr("./assets/Bonus/Bomberman_Range.tga"));
  this->usableTexts["RangeBonus"] = text;

  if ((text = new gdl::Texture) == 0)
    return (false);
  if (!text->load("./assets/BackGround.tga"))
    throw (new LoadErr("./assets/Background.tga"));
  this->usableTexts["BackGround"] = text;

  return (true);
}

bool	GameEngine::initialize(Player *player1, Player *player2, std::vector<IA *> ia)
{
  glm::mat4 projection;
  Image     *load = new Image("./assets/BackGround2.tga");

  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  projection = glm::ortho(0.0f, 1920.0f, 1080.0f, 0.0f, -1.0f, 1.0f);
  this->shader.bind();
  this->shader.setUniform("view", glm::mat4(1));
  this->shader.setUniform("projection", projection);
  load->constructFor2d(0, 0);
  load->draw(this->shader, glm::vec3(1, 1, 1));
  this->context.flush();
  if ((this->clock = new gdl::Clock) == 0)
    return (false);
  try
    {
      if (this->initTextures() == false)
	return (false);
      if (this->initModels() == false)
	return (false);
    }
  catch (AExcept *err)
    {
      std::cerr << "Problem during Load, Problem is : " << std::endl;
      err->printErr();
      delete err;
      return (false);
    }

  this->initForms(player1, player2, ia);
  if (this->initObjects() == false)
    return (false);

  if (!(this->player1 = new PlayerGraph(this->map, this->width, this->height, player1, this->shader, 1, this->usableModels["Marvin"], this->splitScreen)))
    return false;
  if (!this->player1->initialize())
    return false;

  if (this->splitScreen)
    {
      if (!(this->player2 = new PlayerGraph(this->map, this->width, this->height, player2, this->shader, 2, this->usableModels["Marvin"], this->splitScreen)))
	return false;
      if (!this->player2->initialize())
	return false;
    }

  this->choose[Wall] = &GameEngine::getObjFromWall;
  this->choose[Bomb] = &GameEngine::getObjFromBomb;
  this->choose[Bonus] = &GameEngine::getObjFromBonus;
  if (!(this->plan = new Plan(static_cast<float>(this->map->getWidth()), static_cast<float>(this->map->getLength()), 0.0, this->usableTexts["Rusty"])))
    return false;

  if (!this->plan->initialize(this->objGeo["Plan"]))
    return false;

  return true;
}

bool	GameEngine::update()
{
  this->context.updateClock(*(this->clock));
  this->context.updateInputs(this->input);
  if (this->input.getInput(SDL_QUIT) || this->input.getInput(SDLK_DELETE))
    return false;
  this->player1->update(*(this->clock), this->input);
  if (this->splitScreen)
    this->player2->update(*(this->clock), this->input);
  return true;
}

void	setPos(Uint &val, Uint comp)
{
  if (val > comp)
    val = 0;
}

bool	GameEngine::initObjects()
{
  Cube	*objs;
  Plan	*plan;

  if (!(objs = new Cube(1, this->usableTexts["Crate"])))
    return (false);
  objs->initialize(this->objGeo["Cube"]);
  this->drawObjects["BreakableWall"] = objs;

  if (!(objs = new Cube(1, this->usableTexts["MetalCrate"])))
    return (false);
  objs->initialize(this->objGeo["Cube"]);
  this->drawObjects["UnbreakableWall"] = objs;

  if (!(objs = new Cube(1, this->usableTexts["RandomBonus"])))
    return (false);
  objs->initialize(this->objGeo["Cube"]);
  this->drawObjects["RandomBonus"] = objs;

  if (!(objs = new Cube(1, this->usableTexts["Bomb"])))
    return (false);
  objs->initialize(this->objGeo["Cube"]);
  this->drawObjects["Bomb"] = objs;

  if (!(objs = new Cube(1, this->usableTexts["Explosion"])))
    return (false);
  objs->initialize(this->objGeo["Explosion"]);
  this->drawObjects["Explosion"] = objs;

  if (!(objs = new Cube(1, this->usableTexts["SpeedBonus"])))
    return (false);
  objs->initialize(this->objGeo["Cube"]);
  this->drawObjects["SpeedBonus"] = objs;

  if (!(objs = new Cube(1, this->usableTexts["HpBonus"])))
    return (false);
  objs->initialize(this->objGeo["Cube"]);
  this->drawObjects["HpBonus"] = objs;

  if (!(objs = new Cube(1, this->usableTexts["ShieldBonus"])))
    return (false);
  objs->initialize(this->objGeo["Cube"]);
  this->drawObjects["ShieldBonus"] = objs;

  if (!(objs = new Cube(1, this->usableTexts["BombBonus"])))
    return (false);
  objs->initialize(this->objGeo["Cube"]);
  this->drawObjects["BombBonus"] = objs;

  if (!(objs = new Cube(1, this->usableTexts["RangeBonus"])))
    return (false);
  objs->initialize(this->objGeo["Cube"]);
  this->drawObjects["RangeBonus"] = objs;

  if (!(plan = new Plan(1.0f, 1.0f, 1.0f, this->usableTexts["White"])))
    return (false);
  plan->initialize(this->objGeo["PlayerSpot"]);
  this->drawObjects["Spot"] = plan;

  if (!(plan = new Plan(62.50f, 2.0f, 112.0f, this->usableTexts["BackGround"])))
    return (false);
  plan->initialize(this->objGeo["BackGround"]);
  this->drawObjects["BackGround"] = plan;
  return (true);
}

AObjectGraph	*GameEngine::getObjFromWall(const AObject *wall)
{
  if (wall && wall->getWallType() == Breakable)
    return (this->drawObjects["BreakableWall"]);
  else
    return (this->drawObjects["UnbreakableWall"]);
  return (0);
}

AObjectGraph	*GameEngine::getObjFromBonus(const AObject *item)
{
  bonusType	bonus = item->getBonusType();

  return (this->drawObjects[this->bonusObjects[bonus]]);
}

AObjectGraph	*GameEngine::getObjFromBomb(const AObject *)
{
  return (this->drawObjects["Bomb"]);
}

AObjectGraph	*GameEngine::getObjFromCase(const Case *square)
{
  AObject	*content;
  objType	type;

  content = square->getObj();
  if (content)
    type = content->getType();
  else
    return (0);
  return ((this->*choose[type])(content));
}

void	GameEngine::getPlayerFromSquare(std::vector<AObjectGraph *> &, Case *square, Uint, Uint)
{
  std::list<Player *>::iterator	it;
  std::list<Player *> list = square->getPlayers();
  MyModel	*model;

  for (it = list.begin(); it != list.end(); it++)
    {
      if ((*it)->isActive())
	model = this->usableModels["Marvin"];
      else
	model = this->usableModels["StaticMarvin"];
      model->setAngle((*it)->getDirection());
      model->setPos(static_cast<float>((*it)->getY()), static_cast<float>((*it)->getX()));
      model->draw(this->shader, *(this->clock));
      this->playerSpots[(*it)->getId()]->moveOf(static_cast<float>((*it)->getY() - 0.5),
						 static_cast<float>((*it)->getX() - 0.5));
      this->playerSpots[(*it)->getId()]->draw(this->shader, *(this->clock));
    }
}
std::vector<AObjectGraph *>	GameEngine::getObjectsFromMap(const Player *play)
{
  Uint	x = static_cast<int>(play->getX());;
  Uint	y = static_cast<int>(play->getY());;
  Uint	keepX = x;
  Uint	keepY = y;
  std::vector<AObjectGraph *>	list;
  Case	*square;
  AObjectGraph	*cube;
  Uint		dist = 25;
  Uint		heightDist = 20;

  x -= dist - 6;
  y -= dist;
  setPos(x, this->map->getWidth());
  setPos(y, this->map->getLength());
  while (y < keepY + (heightDist + 1) && y < this->map->getLength())
    {
      while (x < keepX + (dist + 1) && x < this->map->getWidth())
	{
	  square = this->map->atMap(x, y);
	  cube = getObjFromCase(square);
	  if (!(square->getPlayers().empty()))
	    getPlayerFromSquare(list, square, x, y);
	  if (cube != 0)
	    {
	      cube->moveOf(static_cast<int>(y), static_cast<int>(x));
	      cube->draw(this->shader, *(this->clock));
	    }
	  x += 1;
	}
      x = keepX - dist - 6;
      setPos(x, this->map->getWidth());
      y += 1;
    }
  return (list);
}

void	delObjects(std::vector<AObjectGraph *> vec)
{
  for (Uint n = 0; n < vec.size(); n++)
    delete (vec[n]);
}

void	GameEngine::updateBombs(std::list<t_explod *> &explodes, bool modify)
{
  std::list<t_explod *>::iterator it = explodes.begin();
  AObjectGraph	*expl;

  while (it != explodes.end() && !(explodes.empty()))
    {
      if ((*it)->framesLeft == 0)
	{
	  delete (*it);
	  it = explodes.erase(it);
	}
      else
	{
	  expl = this->drawObjects["Explosion"];
	  if (expl == 0)
	    throw std::exception();
	  expl->moveOf(static_cast<float>((*it)->y), static_cast<float>((*it)->x));
	  expl->draw(this->shader, *(this->clock));
	  if (modify)
	    (*it)->framesLeft -= 1;
	  ++it;
	}
    }
}

const std::string	getScore(const Player *play)
{
  std::string	score = "Player score is ";
  std::ostringstream	convert;

  convert << play->getScore();
  score += convert.str();
  return (score);
}

const std::string	getHp(const Player *play)
{
  std::string	score = "Player hp is ";
  std::ostringstream	convert;

  convert << play->getHp();
  score += convert.str();
  return (score);
}

void	GameEngine::affInfos(const PlayerGraph *player) const
{
  gdl::Texture	*font = TextureManager::Instance().getFont();
  Text	hp;
  Text	score;
  glm::mat4 projection;

  projection = glm::ortho(0.0f, 1920.0f, 1080.0f, 0.0f, -1.0f, 1.0f);
  this->shader.bind();
  this->shader.setUniform("view", glm::mat4(1));
  this->shader.setUniform("projection", projection);
  score.setFont(font);
  hp.setFont(font);
  score.constructFor2d(getScore(player->getPlayer()), 0, 0);
  hp.constructFor2d(getHp(player->getPlayer()), 0, 20);
  hp.draw(this->shader, glm::vec3(1, 2, 0));
  score.draw(this->shader, glm::vec3(1, 2, 0));
}

void	GameEngine::drawPlayer(PlayerGraph *player)
{
  this->affInfos(player);
  player->resetShader(this->shader);
  player->lookCamera(this->shader);
  this->plan->draw(this->shader, *(this->clock));
  this->context.updateClock(*(this->clock));
  getObjectsFromMap(player->getPlayer());
  this->context.updateClock(*(this->clock));  
  this->drawObjects["BackGround"]->moveOf(static_cast<float>(player->getPlayer()->getY() - 30.0), static_cast<float>(player->getPlayer()->getX() - 30.0));
  this->drawObjects["BackGround"]->draw(this->shader, *(this->clock));
}

void	GameEngine::disableSplit() const
{
  glViewport(0, 0, this->width, this->height);
}

void	GameEngine::draw(std::list<t_explod *> &explodes)
{
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (this->splitScreen && this->player2->getPlayer()->getHp() > 0 && this->player1->getPlayer()->getHp())
    glViewport(0, 0, this->width / 2, this->height);
  else
    {
      glViewport(0, 0, this->width, this->height);
      this->player1->disableSplit(this->width, this->height, this->shader);
    }
  if (this->player1->getPlayer()->getHp())
    {
      this->drawPlayer(this->player1);
      if (this->splitScreen && this->player2->getPlayer()->getHp() > 0)
	this->updateBombs(explodes, false);
      else
	this->updateBombs(explodes, true);
    }
  if (this->player1->getPlayer()->getHp() > 0)
    glViewport(this->width / 2, 0, this->width / 2, this->height);
  else
    {
      glViewport(0, 0, this->width, this->height);
      this->player2->disableSplit(this->width, this->height, this->shader);
    }
  if (this->splitScreen && this->player2->getPlayer()->getHp() > 0)
    {
      this->drawPlayer(this->player2);
      this->updateBombs(explodes, true);
    }
  this->context.flush();
}
