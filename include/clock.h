#ifndef _CLOCK_H_
#define _CLOCK_H_

#include <iostream>
#include <string>

#include "SDL.h"

class Clock {
 public:
  /* constructor */
  Clock(){};

  /* methods */
  void start();
  void pause();
  bool isTimeOut();
  std::string getCurTime();
  void deductTime();

 private:
  Uint32 startTime;
  Uint32 punishment = 0;
  bool isPaused = true;
  float timeElapsed = 0.0f;
  float totalTime = 600000.0f;
};

#endif /* _CLOCK_H_ */