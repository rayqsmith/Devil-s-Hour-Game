#include "room.h"
using namespace tinyxml2;

/**
 * @brief Construct a new Room:: Room object
 */
Room::Room() {
  Vec2d vec(400, 300);
  this->size = vec;
  type = Rooms::bedroom;
}

/**
 * @brief Construct a new Room:: Room object
 *
 * @param size
 */
Room::Room(Vec2d size) { this->size = size; }

/**
 * @brief Construct a new Room:: Room object
 *
 * @param size
 * @param entityList
 */
Room::Room(Vec2d size, std::vector<Entity>& entityList) {
  this->size = size;
  this->entityList = entityList;
  type = Rooms::bedroom;
}

/**
 * @brief Construct a new Room:: Room object
 *
 * @param r : room enum
 */
Room::Room(Rooms r) {
  getEntities(r);
  type = r;
}

/**
 * @brief Get entity list according to the room type
 *
 * @param r : room type
 */
void Room::getEntities(Rooms r) {
  std::string f;
  switch (r) {
    case Rooms::bathroom:
      f = "../data/rooms/bathroom.xml";
      break;
    case Rooms::bedroom:
      f = "../data/rooms/bedroom.xml";
      break;
    case Rooms::kitchen:
      f = "../data/rooms/kitchen.xml";
      break;
    case Rooms::foyer:
      f = "../data/rooms/foyer.xml";
      break;
    case Rooms::hallway:
      f = "../data/rooms/hallway.xml";
      break;

    default:
      f = "../data/rooms/bathroom.xml";
      break;
  }
  generateEntityList(f);
}

/**
 * @brief Private function that helps generate entity list
 *
 * @param f : room data file name
 * @return int : 0 if failed, 1 if successful
 */
int Room::generateEntityList(std::string& f) {
  // load file
  XMLDocument xmlDoc;
  xmlDoc.LoadFile(f.c_str());

  // find root
  XMLElement* pRoot = xmlDoc.FirstChildElement("room");
  if (!pRoot) {
    std::cout << "No XML root!" << std::endl;
    return 0;
  }

  // find width and height
  XMLElement* pElement = pRoot->FirstChildElement("width");
  if (!pElement) {
    std::cout << "No width element" << std::endl;
    return 0;
  }
  int width;
  pElement->QueryIntText(&width);

  pElement = pRoot->FirstChildElement("height");
  int height;
  pElement->QueryIntText(&height);

  this->size = Vec2d(width, height);

  // Query room boundaries
  pElement = pRoot->FirstChildElement("boundX");
  pElement->QueryIntText(&boundX);

  pElement = pRoot->FirstChildElement("boundY");
  pElement->QueryIntText(&boundY);

  pElement = pRoot->FirstChildElement("boundW");
  pElement->QueryIntText(&boundW);

  pElement = pRoot->FirstChildElement("boundH");
  pElement->QueryIntText(&boundH);

  // Query player born position
  pElement = pRoot->FirstChildElement("bornX");
  pElement->QueryIntText(&bornX);

  pElement = pRoot->FirstChildElement("bornY");
  pElement->QueryIntText(&bornY);

  // Get the entity list
  XMLElement* pListElement = pRoot->FirstChildElement("entity");
  while (pListElement) {
    // Query w, h, x, y
    int w, h, x, y;
    bool isEntity;

    pElement = pListElement->FirstChildElement("name");
    if (!pElement) return 0;
    const char* s = pElement->GetText();
    std::string name(s);

    pElement = pListElement->FirstChildElement("w");
    if (!pElement) return 0;
    pElement->QueryIntText(&w);

    pElement = pListElement->FirstChildElement("h");
    if (!pElement) return 0;
    pElement->QueryIntText(&h);

    pElement = pListElement->FirstChildElement("x");
    if (!pElement) return 0;
    pElement->QueryIntText(&x);

    pElement = pListElement->FirstChildElement("y");
    if (!pElement) return 0;
    pElement->QueryIntText(&y);

    pElement = pListElement->FirstChildElement("isEntity");
    if (!pElement) return 0;
    pElement->QueryBoolText(&isEntity);

    // Push entity into the list
    Entity e(x, y, w, h, name, isEntity);
    this->entityList.push_back(e);

    // Move pointer to next sibling
    pListElement = pListElement->NextSiblingElement("entity");
  }

  // Success.
  return 1;
}