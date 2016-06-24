#include	"PlayerGraph.hpp"

PlayerGraph::PlayerGraph(Map *map, float w, float h, Player* p, gdl::AShader& s, Uint num, MyModel *model, bool splitScreen)
{
  this->map = map;
  this->model = model;
  this->player = p;
  this->x = 0;
  this->y = 0;
  if (splitScreen)
    w /= 2;
  if (num == 2)
    {
      this->keyConf[SDLK_w] = UP;
      this->keyConf[SDLK_s] = DOWN;
      this->keyConf[SDLK_a] = LEFT;
      this->keyConf[SDLK_d] = RIGHT;
      this->keyConf[SDLK_e] = SETBOMB;
    }
  else if (num == 1)
    {
      this->keyConf[SDLK_UP] = UP;
      this->keyConf[SDLK_DOWN] = DOWN;
      this->keyConf[SDLK_LEFT] = LEFT;
      this->keyConf[SDLK_RIGHT] = RIGHT;
      this->keyConf[SDLK_SPACE] = SETBOMB;      
    }
  this->moves[UP] = &PlayerGraph::moveUp;
  this->moves[DOWN] = &PlayerGraph::moveDown;
  this->moves[LEFT] = &PlayerGraph::moveLeft;
  this->moves[RIGHT] = &PlayerGraph::moveRight;
  this->moves[SETBOMB] = &PlayerGraph::placeBomb;
  this->camera.initialize(w, h);
  if (p) {
    glm::vec3  pos(-(this->player->getY()), 0, -(this->player->getX()));
    this->camera.look(pos);
  }
  s.bind();
  s.setUniform("projection", this->camera.getProjection());
}

void	PlayerGraph::resetShader(gdl::AShader &s) const
{
  s.bind();
  s.setUniform("projection", this->camera.getProjection());
}

void	PlayerGraph::disableSplit(float w, float h, gdl::AShader &s)
{
  this->camera.disableSplit(w, h);
  s.setUniform("projection", this->camera.getProjection());
}

PlayerGraph::~PlayerGraph()
{
}

bool PlayerGraph::initialize()
{
  this->speed = 10.0f;
  return true;
}

void PlayerGraph::update(gdl::Clock const &, gdl::Input &i)
{
  this->player->updateBonus();
  for (Keyconf::iterator it = this->keyConf.begin(); it != this->keyConf.end(); ++it) {
    if (i.getKey(it->first))
    {
      if (!this->player->isDead())
        (this->*moves[it->second])();
    }
  }
}

void	PlayerGraph::placeBomb()
{
  this->player->tryPlaceBomb(this->map);
}

void	PlayerGraph::moveUp()
{
  this->model->setAngle(GUp);
  if (this->player->tryMoveUp(this->map))
    this->camera.translate(glm::vec3(0, 0, -1) * 0.02f * static_cast<float>(this->player->getSpeed()));
}

void	PlayerGraph::moveDown()
{
  this->model->setAngle(GDown);
  if (this->player->tryMoveDown(this->map))
    this->camera.translate(glm::vec3(0, 0, 1) * 0.02f * static_cast<float>(this->player->getSpeed()));
}

void	PlayerGraph::moveLeft()
{
  this->model->setAngle(GLeft);
  if (this->player->tryMoveLeft(this->map))
    this->camera.translate(glm::vec3(-1, 0, 0) * 0.02f * static_cast<float>(this->player->getSpeed()));
}

void	PlayerGraph::moveRight()
{
  this->model->setAngle(GRight);
  if (this->player->tryMoveRight(this->map))
    this->camera.translate(glm::vec3(1, 0, 0) * 0.02f * static_cast<float>(this->player->getSpeed()));
}

void PlayerGraph::draw(gdl::AShader &s, gdl::Clock const &c)
{
  if (this->player->getHp() == 0)
    return ;
  this->model->setPos(static_cast<float>(this->player->getY()), static_cast<float>(this->player->getX()));
  
  this->model->draw(s, c);//s, getTransformation(), GL_QUADS);
}

void PlayerGraph::moveOf(int x, int y)
{
  this->x = -x;
  this->y = -y;
  // original : x, 0, y
  this->translate(glm::vec3(-x, 0, -y) * 2.0f);
}

void PlayerGraph::lookCamera(gdl::AShader &s)
{
  s.bind();
  s.setUniform("view", this->camera.getTransformation());
}

const Player	*PlayerGraph::getPlayer() const
{
  return (this->player);
}
