#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <string>

#include "vec2d.h"

class Entity {
 public:
  /* Members */
  std::string name;
  Vec2d position;
  Vec2d size;
  bool isEntity;  // true if the player CANNOT walk on it, false if the player
                  // CAN walk on it

  /* Constructor */
  Entity();
  Entity(float x, float y, float w, float h, std::string name, bool isEntity);
};

#endif /* _ENTITY_H_ */