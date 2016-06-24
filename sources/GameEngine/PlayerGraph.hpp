#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <Texture.hh>
#include <Geometry.hh>
#include "myModel.hpp"
#include "AObject.hpp"
#include "Camera.hpp"
#include "Player.hpp"

typedef unsigned int			Uint;
typedef std::map<Uint, Action>	Keyconf;

class PlayerGraph : public AObjectGraph
{
  typedef void	(PlayerGraph::*moveFunc)();
private:
  std::map<Action, moveFunc>	moves;
  gdl::Texture		texture;
  gdl::Geometry		geometry;
  float			speed;
  Camera		camera;
  MyModel		*model;
  Player		*player;
  Map			*map;
  Keyconf		keyConf;
  void	moveUp();
  void	moveDown();
  void	moveLeft();
  void	moveRight();
  void	placeBomb();
public:
  PlayerGraph(Map *map, float w, float h, Player* p, gdl::AShader& s, Uint num, MyModel *model, bool splitScreen = false);
  virtual ~PlayerGraph();
  virtual bool initialize();
  virtual void update(gdl::Clock const &, gdl::Input &i);
  virtual void draw(gdl::AShader &s, gdl::Clock const &c);
  virtual void moveOf(int x, int y);
  virtual void lookCamera(gdl::AShader &s);
  const Player	*getPlayer() const;
  void		resetShader(gdl::AShader &s) const;
  void		disableSplit(float, float, gdl::AShader &);
  MyModel	*getModel() const {
    return (this->model);
  };
};

#endif
