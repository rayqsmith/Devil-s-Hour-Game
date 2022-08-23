#ifndef _EVENTMANAGER_H_
#define _EVENTMANAGER_H_

#include <SDL.h>

#include <iostream>
#include <string>
#include <vector>

#include "actor.h"
#include "audioView.h"
#include "clock.h"
#include "dialog.h"
#include "dialogManager.h"
#include "gameView.h"
#include "room.h"
#include "stateMonitor.h"
#include "stdio.h"
#include "vec2d.h"

class EventManager {
 public:
  /* constructor */
  EventManager() { this->curRoom.getEntities(Rooms::bedroom); }
  EventManager(GameView* gameView, AudioView* audioView);
  EventManager(GameView* gameView);
  void startScreen(void);
  void loseScreen(void);
  void winScreen(void);
  void startGame(void);
  void handle_event(SDL_Event* event, float deltaTime, float time,
                    bool* running, SDL_Renderer* renderer);
  void playerMovement(float deltaTime, direction direction,
                      SDL_Renderer* renderer);
  void playerInteraction();
  void pauseGame(float time);
  void roomChange(Rooms r);
  void inventoryChange();
  void returnToGame(void);
  void displayGame(void);
  void showDialog(const char* name, const char* text);
  void displayDialog(std::vector<std::string> names,
                     std::vector<std::string> texts);
  void displayDialog(std::string name, std::string text);

  void handlePausedEvent(SDL_Event* event, float deltaTime, float time,
                         bool* running, SDL_Renderer* renderer);

  void handleDialogEvent(SDL_Event* event, float deltaTime, float time,
                         bool* running, SDL_Renderer* renderer);

  void exitEvent(SDL_Event* event, float time, bool* running);

 private:
  int curItem = 0;
  bool gameStarted = false;
  bool isPaused = false;
  bool isDialog = false;
  bool isWinning = false;
  bool isLosing = false;
  bool showEntity = false;

  GameView* gameView;
  AudioView* audioView;
  DialogManager dialogManager;
  Actor mainActor;
  direction curDir;
  Room curRoom;
  StateMonitor stateMonitor;
  Rooms currRoomName;
  Clock clock;
  Inventory inventory;

  std::vector<std::string> testText;
  std::string text1 = "here";
  std::vector<std::string> nameText;
  Dialog curDialog;
};

#endif
