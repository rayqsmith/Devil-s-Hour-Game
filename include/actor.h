#ifndef _ACTOR_H_
#define _ACTOR_H_
#include <iostream>
#include <vector>

#include "entity.h"
#include "room.h"
/**
 * @brief Actor handles all the enities in the game that move independently
 *
 */
class Actor : public Entity {
 public:
  /* constructor */
  Actor();

  /* methods */
  void move(direction d, float deltaTime,
            std::vector<Entity>& entityList); /**< handles movement */
  bool collision(const std::vector<Entity> entityList);
  bool collisionDetection(direction d, std::vector<Entity>& entityList);
  void setBoundary(int x, int y, int w, int h);
  std::string interact(std::vector<Entity>& entityList);
  direction getDirection(void) { return curDir; }

 private:
  /* members */
  float velocity; /**< how fast they move */
  direction curDir;
  Entity entity;  // entity collided into last
  int boundX;
  int boundY;
  int boundW;
  int boundH;

  bool collideWith(direction d, Entity* e);
  bool canWalkOnCollision(const Entity entity);
};

#endif /* _ACTOR_H_ */
