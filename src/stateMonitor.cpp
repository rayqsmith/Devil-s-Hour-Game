#include "stateMonitor.h"

/**
 * @brief Construct a new State Monitor:: State Monitor object
 *
 */
StateMonitor::StateMonitor() { this->currentState = ""; }

/**
 * @brief Update game state.
 *
 * @param s
 * @return int : 2->enters kitchen; 3->enters bathroom; 4->enters main foyer;
 * 5->enters hallway; 6->triggered penalty
 */
int StateMonitor::update(std::string& s) {
  this->currentState = s;
  if (currentState == "k1") return 2;
  if (currentState == "b1") return 3;
  if (currentState == "f1") return 4;
  if (currentState == "h1" || currentState == "h2" || currentState == "h3")
    return 5;
  if (currentState == "b3" || currentState == "k7" || currentState == "e4" ||
      currentState == "f2")
    return 6;
  if (currentState == "f9") return 7;
  return 0;
}
