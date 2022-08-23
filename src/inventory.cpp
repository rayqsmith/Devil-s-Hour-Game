#include "inventory.h"

#include <iostream>

/**
 * @brief Construct a new Inventory and initializes the currentPosition and
 * the items vector
 */
Inventory::Inventory() {
  currentPosition = 0;
  items = {
      "hands", "", "", "", "", "", "", "",
  }; /**< itilialize the items vector with 8 slots */
}

/**
 * @brief Returns the name of the item currently selected in the inventory
 *
 * @return const std::string
 */
const std::string Inventory::getSelectedItem() {
  return items.at(currentPosition);
}

/**
 * @brief Returns the name of the item at the desired position
 *
 * @param position
 * @return const std::string
 */
const std::string Inventory::getItemAtPos(int position) {
  if (position > -1 && position < 8) {  // Check to see if position is valid
    return items.at(position);
  }
  return "";
}

/**
 * @brief Returns a vector of strings containing the names of all items
 *
 * @return const std::vector<std::string>
 */
const std::vector<std::string> Inventory::getAllItems() { return items; }

/**
 * @brief Returns whether an item with a given itemName exists in the inventory
 *
 * @param itemName
 * @return true if the item exists in the inventory
 * @return false if the item is not contained in the inventory
 */
const bool Inventory::itemInInventory(std::string itemName) {
  for (int i = 0; i < items.size(); i++) {
    if (items.at(i) == itemName) {
      return true;
    }
  }
  return false;
}

const bool Inventory::itemHasBeenUsed(std::string itemName) {
  for (int i = 0; i < usedItems.size(); i++) {
    if (usedItems.at(i) == itemName) {
      return true;
    }
  }
  return false;
}

/**
 * @brief Adds a new item to the inventory at an empty space
 *
 * @param itemName
 */
bool Inventory::addItem(std::string itemName) {
  if (itemHasBeenUsed(itemName)) return false;
  for (int i = 0; i < 8; i++) {
    if (items[i] == itemName) return false;
    if (items.at(i) == "") {
      items.at(i) = itemName;
      return true;
    }
  }
  return false;
}

/**
 * @brief Removes the item at the current position from the inventory
 *
 */
void Inventory::removeItem() {
  usedItems.push_back(items.at(currentPosition));
  if (items.at(currentPosition) != "steak-knife")  // Sepcial case: Never remove
                                                   // steak knife from inventory
    items.at(currentPosition) = "";
}

/**
 * @brief Removes an item from usedItems list
 *
 * @param itemName
 */
void Inventory::removeUsedItem(std::string itemName) {
  for (int i = 0; i < usedItems.size(); i++) {
    if (usedItems.at(i) == itemName) {
      usedItems.at(i) = "";
    }
  }
}

/**
 * @brief Moves the current position in the inventory up by one
 *
 */
void Inventory::changeSelectedItem() {
  Inventory::currentPosition = (Inventory::currentPosition + 1) % 8;
}

void Inventory::resetInventory() {
  items = {
      "hands", "", "", "", "", "", "", "",
  };
  usedItems = {};
}