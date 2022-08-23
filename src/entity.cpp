#include "entity.h"

/**
 * @brief Construct a new Entity:: Entity object
 * 
 */
Entity::Entity() {
  Vec2d location = Vec2d(0, 0);
  Vec2d size = Vec2d(0, 0);
  this->position = location;
  this->size = size;
  this->name = name;
  this->isEntity = isEntity;
}

/**
 * @brief Construct a new Entity:: Entity object
 * 
 * @param x 
 * @param y 
 * @param w 
 * @param h 
 * @param name 
 * @param isEntity 
 */
Entity::Entity(float x, float y, float w, float h, std::string name,
               bool isEntity) {
  Vec2d location = Vec2d(x, y);
  Vec2d size = Vec2d(w, h);
  this->position = location;
  this->size = size;
  this->name = name;
  this->isEntity = isEntity;
}
