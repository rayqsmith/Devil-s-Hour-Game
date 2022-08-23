#include "clock.h"

/**
 * @brief Start/Reset the timer
 * 
 */
void Clock::start() {
  isPaused = false;
  startTime = SDL_GetTicks();
  punishment = 0;
  // std::cout << "start time:" << startTime << std::endl;
}

/**
 * @brief Check if time is out.
 * 
 * @return true 
 * @return false 
 */
bool Clock::isTimeOut() {
  return (SDL_GetTicks() + punishment - startTime) > totalTime;
}

/**
 * @brief Get current time to display in the game
 * 
 * @return std::string : current time by string
 */
std::string Clock::getCurTime() {
  Uint32 curTime = SDL_GetTicks() + punishment;
  // std::cout << "cur time:" << curTime << std::endl;
  std::string s = "02:";
  int minute = (curTime - startTime) / totalTime * 60;
  if (minute < 10) s += "0";
  s += std::to_string(minute);
  if (minute == 60) s = "03:00";
  // std::cout << s << std::endl;
  return s;
}

/**
 * @brief Deduct 15 min from the player's total time. 
 * 
 */
void Clock::deductTime() { punishment += 150000; }
