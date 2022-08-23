#ifndef _ROOM_H_
#define _ROOM_H_

#include <tinyxml2.h>

#include <iostream>
#include <string>
#include <vector>

#include "constants.h"
#include "entity.h"

class Room : public Entity {
 public:
  /* constructor */
  Room();
  Room(Vec2d vec);
  Room(Vec2d vec, std::vector<Entity>& entityList);
  Room(Rooms r);

  /* Members */
  Rooms type;
  Vec2d size;
  int boundX = 0;
  int boundY = 0;
  int boundW = 1024;
  int boundH = 768;
  int bornX = 0;
  int bornY = 0;
  std::vector<Entity> entityList;

  /* Get entity list from xml file */
  void getEntities(Rooms r);

 private:
  int generateEntityList(std::string& s);
};

#endif /* _ROOM_H_ */