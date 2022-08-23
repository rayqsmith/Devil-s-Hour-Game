#include "inventory.h"

#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  Inventory inv;

  inv.addItem("water");
  inv.addItem("key");

  std::cout << inv.getSelectedItem() << std::endl;
  for (auto temp : inv.getAllItems()) {
    std::cout << temp << std::endl;
  }

  inv.changeSelectedItem();
  std::cout << "New Selected Item" << inv.getSelectedItem() << std::endl;

  inv.removeItem();
  for (auto temp : inv.getAllItems()) {
    std::cout << "After Removal" << temp << std::endl;
  }
}