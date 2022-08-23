#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <string>
#include <vector>

class Inventory {
  std::vector<std::string> items; /**< holds the items */
  std::vector<std::string>
      usedItems; /**< holds the items the player has used */

 public:
  Inventory(); /**< constructor initializes currentPosition and item vector */
  const std::string getSelectedItem(); /**< gets the selected item */
  const std::string getItemAtPos(
      int position); /**< gets the item at the selected position */
  const std::vector<std::string>
  getAllItems(); /**< gets a list of all the items */
  const bool itemInInventory(
      std::string itemName); /**< returns true if the player
                          has an item, false if not */
  const bool itemHasBeenUsed(std::string itemName); /**< returns true if the
                        player has used an item, false if not */

  void changeSelectedItem();          /**< change the selected item*/
  bool addItem(std::string itemName); /**< adds a given item to the inventory*/
  void removeItem(); /**< removes the item at the current position*/
  void removeUsedItem(
      std::string itemName); /**< removes the item from the usedItems list*/

  void resetInventory(); /**< resets the inventory to hold nothing*/

  int currentPosition;
  /**
   * @brief Construct a new Inventory object
   *
   */
};
#endif
