#ifndef _DIALOG_H_
#define _DIALOG_H_

#include <iostream>
#include <string>
#include <vector>

#include "constants.h"
#include "tinyxml2.h"
#include "vec2d.h"

struct dialog {
  int id;
  int x1 = -1, x2 = -1, y1 = -1, y2 = -1;
  std::string triggerObject;
  std::string useItem;
  std::string pickItem;
  std::string triggerState;
  std::string transitToState;
  std::vector<std::string> speakers;
  std::vector<std::string> texts;
};

class Dialog {
 public:
  Dialog(){};
  /**
   *  @brief Construct a new Dialog object
   *
   * @param r : room that correspond to the xml file
   */
  Dialog(Rooms r);

  /**
   * @brief generate dialog list from xml
   *
   * @param r : room that correspond to the xml file
   */
  void generateDialogList(Rooms r);

  /**
   * @brief trigger a certain dialog from the dialog list
   *
   * @param loc character's location
   * @param object object that actor interacts with
   * @param item item used by the actor
   * @param curState current game state
   * @return int : return the id of the dialog if triggered, return -1 if no
   * dialog is triggered.
   */
  int triggerDialog(Vec2d loc, std::string& object, std::string& item,
                    std::string& curState);

  std::vector<dialog> dialogList;

 private:
  int parseDialogFromFile(std::string& f);
};
#endif /* _DIALOG_H_ */