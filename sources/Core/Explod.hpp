
#ifndef EXPLOD_HPP__
# define EXPLOD_HPP__

#include "myModel.hpp"

typedef struct s_explod
{
  s_explod(unsigned int px, unsigned int py, dir d) { this->x = px; this->y = py; this->direction = d; 
    this->framesLeft = 10;}
  unsigned int framesLeft;
  unsigned int	x;
  unsigned int	y;
  dir		direction;
} t_explod;

#endif
