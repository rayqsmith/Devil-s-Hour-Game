#ifndef _STATEMONITOR_H_
#define _STATEMONITOR_H_

#include <string>

#include "constants.h"

class StateMonitor {
 public:
  /* constructor */
  StateMonitor();

  /* update current game state */
  int update(std::string& s);

  std::string currentState;
};

#endif /* _STATEMONITOR_H_ */