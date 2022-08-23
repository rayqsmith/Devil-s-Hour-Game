#include "dialog.h"
using namespace tinyxml2;

/**
 * @brief Construct a new Dialog:: Dialog object
 *
 * @param r : room type
 */
Dialog::Dialog(Rooms r) { generateDialogList(r); }

/**
 * @brief Generate dialog list
 *
 * @param r : room type
 */
void Dialog::generateDialogList(Rooms r) {
  std::string f;
  switch (r) {
    case Rooms::bathroom:
      f = "../data/dialogs/bathroom_dialog.xml";
      break;
    case Rooms::bedroom:
      f = "../data/dialogs/bedroom_dialog.xml";
      break;
    case Rooms::kitchen:
      f = "../data/dialogs/kitchen_dialog.xml";
      break;
    case Rooms::foyer:
      f = "../data/dialogs/foyer_dialog.xml";
      break;

    case Rooms::hallway:
      f = "../data/dialogs/hallway_dialog.xml";
      break;

    default:
      f = "../data/dialogs/bathroom_dialog.xml";
      break;
  }
  if (!parseDialogFromFile(f)) {
    std::cout << "Can't generate dialog list from XML!" << std::endl;
  }
}

/**
 * @brief helper function to parse XML file
 *
 * @param f : file path
 * @return int : 0 if failed, 1 if success.
 */
int Dialog::parseDialogFromFile(std::string& f) {
  XMLDocument xmlDoc;
  xmlDoc.LoadFile(f.c_str());

  // find root
  XMLElement* pRoot = xmlDoc.FirstChildElement("DialogList");
  if (!pRoot) {
    std::cout << "No XML root!" << std::endl;
    return 0;
  }

  // Get the dialog list
  XMLElement* pListElement = pRoot->FirstChildElement("Dialog");

  while (pListElement) {
    dialog d;
    XMLElement* pElement;

    // Query id
    // int id;
    pElement = pListElement->FirstChildElement("id");
    if (!pElement) return 0;
    pElement->QueryIntText(&(d.id));

    if (f == "../data/dialogs/foyer_dialog.xml") std::cout << d.id << std::endl;

    // Query trigger location
    XMLElement* pSubElement =
        pListElement->FirstChildElement("triggerLocation");

    pElement = pSubElement->FirstChildElement("x1");
    if (pElement) pElement->QueryIntText(&(d.x1));

    pElement = pSubElement->FirstChildElement("x2");
    if (pElement) pElement->QueryIntText(&(d.x2));

    pElement = pSubElement->FirstChildElement("y1");
    if (pElement) pElement->QueryIntText(&(d.y1));

    pElement = pSubElement->FirstChildElement("y2");
    if (pElement) pElement->QueryIntText(&(d.y2));

    // std::cout << "loc" << std::endl;

    // Query trigger object
    pElement = pListElement->FirstChildElement("triggerObject");
    if (!pElement) return 0;
    const char* s = pElement->GetText();
    if (!s)
      d.triggerObject = "";
    else {
      std::string triggerObject(s);
      d.triggerObject = triggerObject;
    }

    // Query used item
    pElement = pListElement->FirstChildElement("useItem");
    if (!pElement) return 0;
    s = pElement->GetText();
    if (!s)
      d.useItem = "";
    else {
      std::string useItem(s);
      d.useItem = useItem;
    }

    // Query picked item
    pElement = pListElement->FirstChildElement("pickItem");
    if (!pElement) return 0;
    s = pElement->GetText();
    if (!s)
      d.pickItem = "";
    else {
      std::string pickItem(s);
      d.pickItem = pickItem;
    }

    // Query triggerState
    pElement = pListElement->FirstChildElement("triggerState");
    if (!pElement) return 0;
    s = pElement->GetText();
    if (!s)
      d.triggerState = "";
    else {
      std::string triggerState(s);
      d.triggerState = triggerState;
    }

    // Query transit to state
    pElement = pListElement->FirstChildElement("transitToState");
    if (!pElement) return 0;
    s = pElement->GetText();
    if (!s)
      d.transitToState = "";
    else {
      std::string transitToState(s);
      d.transitToState = transitToState;
    }

    // Query text List
    pSubElement = pListElement->FirstChildElement("textList");
    pElement = pSubElement->FirstChildElement("text");
    while (pElement) {
      // Query speaker
      s = pElement->Attribute("speaker");
      std::string speaker(s);
      d.speakers.push_back(speaker);

      // Query text
      s = pElement->GetText();
      std::string text(s);
      d.texts.push_back(text);

      // Move pointer to next sibling
      pElement = pElement->NextSiblingElement("text");
    }

    // push d into dialog list
    this->dialogList.push_back(d);

    // Move pointer to next sibling
    pListElement = pListElement->NextSiblingElement("Dialog");
  }

  return 1;
}

bool matchLocation(dialog d, Vec2d loc) {
  // return true if not specified
  if (d.x1 == 0 && d.x2 == 0 && d.y1 == 0 && d.y2 == 0) return true;
  return loc.x >= d.x1 && loc.x <= d.x2 && loc.y >= d.y1 && loc.y <= d.y2;
}

bool matchObject(dialog d, std::string& object) {
  if (d.triggerObject == "") return true;
  return d.triggerObject == object;
}

bool matchItem(dialog d, std::string& item) {
  if (item == "hands" && d.useItem == "") return true;
  return item == d.useItem;
}

bool matchState(dialog d, std::string& curState) {
  if (d.triggerState == "") return true;
  return d.triggerState == curState;
}

/**
 * @brief Query the dialog to trigger in the dialog list
 *
 * @param loc
 * @param object
 * @param item
 * @param curState
 * @return int : return the id of the dialog if triggered, return -1 if no
 * dialog is triggered.
 */
int Dialog::triggerDialog(Vec2d loc, std::string& object, std::string& item,
                          std::string& curState) {
  for (int i = 1; i < dialogList.size(); ++i) {
    dialog d = dialogList[i];
    if (matchObject(d, object) && matchItem(d, item) && matchState(d, curState))
      return i;
  }
  return -1;
}
