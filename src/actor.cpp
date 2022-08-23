#include "actor.h"

/**
 * @brief Construct a new Actor:: Actor object
 *
 */
Actor::Actor() {
  velocity = 0.5f;
  position.x = 100;
  position.y = 400;
  size.x = 60;  // width
  size.y = 60;  // height

  curDir = direction::RIGHT;
}

/**
 * @brief Set the movement boundary of the actor
 *
 * @param x
 * @param y
 * @param w
 * @param h
 */
void Actor::setBoundary(int x, int y, int w, int h) {
  this->boundX = x;
  this->boundY = y;
  this->boundW = w;
  this->boundH = h;
}

/**
 * @brief Moves character in a desired direction
 *
 * @param direction: direction the character is headed
 * @param deltaTime: time elapsed
 */
void Actor::move(direction direction, float deltaTime,
                 std::vector<Entity>& entityList) {
  curDir = direction;
  // if (collisionDetection(direction, entityList)) return;
  switch (direction) {
    case direction::UP:
      position.y += deltaTime * -velocity;
      if (position.y < boundY) position.y = boundY;
      break;
    case direction::DOWN:
      position.y += deltaTime * velocity;
      if (position.y + size.y > boundY + boundH)
        position.y = boundY + boundH - size.y;
      break;
    case direction::RIGHT:
      position.x += deltaTime * velocity;
      if (position.x + size.x > boundX + boundW)
        position.x = boundX + boundW - size.x;
      break;
    case direction::LEFT:
      position.x += deltaTime * -velocity;
      if (position.x < boundX) position.x = boundX;
      break;
  }
}
/**
 * @brief Checks whether player collides with another entity  returns true if
 * performed a successful collision
 *
 * @param size
 * @returns true if a collision was successful, false otherwise
 */
bool Actor::collision(const std::vector<Entity> entityList) {  // Entity
  // check if it hits against any inside the entity list
  int n = entityList.size();
  for (int i = 0; i < n; i++) {
    entity = entityList[i];
    // checking horizontally
    if ((entity.position.x <= (position.x + size.x)) &&
        (position.x <= (entity.position.x + entity.size.x)))
      // checking vertically
      if ((entity.position.y <= (position.y + size.y)) &&
          (position.y <= (entity.position.y + entity.size.y))) {
        // adjust position based on which side actor is facing and if object can
        // be walked on
        if (!canWalkOnCollision(entity) && entity.isEntity) {
          switch (curDir) {
            case direction::UP:
              position.y = entity.position.y + entity.size.y;
              break;
            case direction::DOWN:
              position.y = entity.position.y - size.y;
              break;
            case direction::LEFT:
              position.x = entity.position.x + entity.size.x;
              break;
            case direction::RIGHT:
              position.x = entity.position.x - size.x;
              break;
          }
        }
        return true;
      }
  }

  return false;
}
/**
 * @brief After collision, this makes sure the character can walk next to object
 * only if it's not facing the object
 *
 * @param size
 * @returns true if character can walk this direction, false otherwise
 */
bool Actor::canWalkOnCollision(const Entity entity) {
  switch (curDir) {
    case direction::UP:
    case direction::DOWN:
      // check if actor is on the left side and right side of the object
      if ((position.x + size.x == entity.position.x) ||
          (position.x == entity.position.x + entity.size.x))
        return true;
    case direction::LEFT:
    case direction::RIGHT:
      // check top then bottom
      if ((position.y + size.y == entity.position.y) ||
          (position.y == entity.position.y + entity.size.y))
        return true;
  }
  return false;
}

/**
 * @brief Determine whether the actor is colliding with an entity in the given
 * direction
 *
 * @param d
 * @param e
 * @return true if they collide
 * @return false if they don't
 */
bool Actor::collideWith(direction d, Entity* e) {
  auto x1min = this->position.x;
  auto x1max = this->position.x + this->size.x;
  auto y1min = this->position.y;
  auto y1max = this->position.y + this->size.y;
  auto x2min = e->position.x;
  auto x2max = e->position.x + e->size.x;
  auto y2min = e->position.y;
  auto y2max = e->position.y + e->size.y;

  if (x1min <= x2max && x2min <= x1max && y1min <= y2max && y2min <= y1max) {
    if (!e->isEntity) return true;
    switch (d) {
      case direction::UP:
        return x1min < x2max && x2min < x1max && y1max > y2max;
      case direction::DOWN:
        return x1min < x2max && x2min < x1max && y1min < y2min;
      case direction::LEFT:
        return y1min < y2max && y2min < y1max && x1max > x2max;
      case direction::RIGHT:
        return y1min < y2max && y2min < y1max && x1min < x2min;

      default:
        return true;
    }
  }
  return false;
}

/**
 * @brief Determine whether the actor collide with anything in the entity list
 *
 * @param d
 * @param entityList
 * @return true
 * @return false
 */
bool Actor::collisionDetection(direction d, std::vector<Entity>& entityList) {
  Entity* e;
  for (int i = 0; i < entityList.size(); ++i) {
    e = &entityList[i];
    if (collideWith(d, e)) {
      if (e->isEntity) {
        switch (d) {
          case direction::UP:
            position.y = e->position.y + e->size.y;
            break;
          case direction::DOWN:
            position.y = e->position.y - this->size.y;
            break;
          case direction::LEFT:
            position.x = e->position.x + e->size.x;
            break;
          case direction::RIGHT:
            position.x = e->position.x - this->size.x;
            break;

          default:
            break;
        }
      }
      return true;
    }
  }
  return false;
}

/**
 * @brief Return the name of the entity among the entity list that you are
 * interacting with
 *
 * @param entityList
 * @return std::string : name of the entity
 */
std::string Actor::interact(std::vector<Entity>& entityList) {
  Entity* e;
  for (int i = 0; i < entityList.size(); ++i) {
    e = &entityList[i];
    if (collideWith(this->curDir, e)) {
      return e->name;
    }
  }
  return "";
}