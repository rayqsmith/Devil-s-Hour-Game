#include "eventManager.h"

/**
 * @brief Construct a new Event Manager:: Event Manager object
 *
 * @param gameView
 * @param audioView
 */
EventManager::EventManager(GameView* gameView, AudioView* audioView) {
  this->curRoom.getEntities(Rooms::bathroom);
  this->gameView = gameView;
  this->audioView = audioView;

  std::vector<std::string> Text = {"test", "dsd"};
  std::vector<std::string> name = {"name1", "name2"};

  this->dialogManager = DialogManager();

  this->testText.assign(Text.begin(), Text.end());

  this->nameText.assign(name.begin(), name.end());
}

/**
 * @brief Construct a new Event Manager:: Event Manager object
 *
 * @param gameView
 */
EventManager::EventManager(GameView* gameView) {
  this->curRoom.getEntities(Rooms::bathroom);
  this->gameView = gameView;
  this->audioView = NULL;

  std::vector<std::string> Text = {"test", "dsd"};
  std::vector<std::string> name = {"name1", "name2"};

  this->dialogManager = DialogManager();

  this->testText.assign(Text.begin(), Text.end());

  this->nameText.assign(name.begin(), name.end());
}

/**
 * @brief Takes in the events from the SDL event queue and processes it within
 * the game
 *
 * @param event - the SDL event
 * @param deltaTime - the time change between events last event
 */
void EventManager::handle_event(SDL_Event* event, float deltaTime, float time,
                                bool* running, SDL_Renderer* renderer) {
  Uint8 const* keystate = SDL_GetKeyboardState(NULL);

  keystate = SDL_GetKeyboardState(NULL);

  // quit event
  if (event->type == SDL_QUIT) {
    exitEvent(event, time, running);
  }

  // start game event
  if (event->key.keysym.sym == SDLK_x && !gameStarted) {
    startGame();
    gameStarted = true;
  } else if (gameStarted) {
    // character movement
    if (!isDialog && !isPaused) {
      if (keystate[SDL_SCANCODE_W]) {
        playerMovement(deltaTime, direction::UP, renderer);
      }
      if (keystate[SDL_SCANCODE_A]) {
        playerMovement(deltaTime, direction::LEFT, renderer);
      }
      if (keystate[SDL_SCANCODE_S]) {
        playerMovement(deltaTime, direction::DOWN, renderer);
      }
      if (keystate[SDL_SCANCODE_D]) {
        playerMovement(deltaTime, direction::RIGHT, renderer);
      }
    }
    if (event->type == SDL_KEYDOWN) {
      if (isPaused == false && isDialog == false) {
        switch (event->key.keysym.sym) {
          case SDLK_e:
            playerInteraction();
            break;

          case SDLK_SPACE:
            playerInteraction();
            break;

          case SDLK_i:
            inventoryChange();
            break;

          case SDLK_ESCAPE:
            pauseGame(time);
            break;

            // // DEBUG

            // case SDLK_z:
            //   isDialog = true;
            //   displayDialog(this->nameText, this->testText);
            //   break;

            // case SDLK_h:
            //   roomChange(Rooms::bedroom);
            //   break;
            // case SDLK_j:
            //   roomChange(Rooms::kitchen);
            //   break;
            // case SDLK_k:
            //   roomChange(Rooms::bathroom);
            //   break;
            // case SDLK_l:
            //   roomChange(Rooms::foyer);
            //   break;
            // case SDLK_p:
            //   roomChange(Rooms::hallway);
            //   break;
            // case SDLK_9:
            //   gameView->drawWinningScreen();
            //   gameView->presentScreen();
            //   gameStarted = false;
            //   break;
            // case SDLK_0:
            //   gameView->drawLosingScreen();
            //   gameView->presentScreen();
            //   gameStarted = false;
            //   break;
            // case SDLK_t:
            //   showEntity = !showEntity
            //   break;
            // case SDLK_1:
            //   clock.deductTime();
            //   break;
        }

        // draw game on screen
        if (!isPaused && !isDialog && gameStarted) {
          displayGame();
        }

        // Pause event
      } else if (isPaused) {
        handlePausedEvent(event, deltaTime, time, running, renderer);
        // Display dialog
      } else if (isDialog) {
        handleDialogEvent(event, deltaTime, time, running, renderer);
      }
      // Draw game to screen
    } else if (isPaused == false && isDialog == false && gameStarted) {
      displayGame();
    }

    // Checking if the timer has run out
    if (clock.isTimeOut()) {
      gameStarted = false;
      loseScreen();
    }
  }
}

/**
 * @brief Handle events when paused.
 *
 * @param event
 * @param deltaTime
 * @param time
 * @param running
 * @param renderer
 */
void EventManager::handlePausedEvent(SDL_Event* event, float deltaTime,
                                     float time, bool* running,
                                     SDL_Renderer* renderer) {
  switch (event->key.keysym.sym) {
    // quit
    case SDLK_q:
      exitEvent(event, time, running);
      break;
    // resume
    case SDLK_r:
      returnToGame();
      break;
    // resume
    case SDLK_ESCAPE:
      returnToGame();
      break;
  }
}

/**
 * @brief Handle dialog events
 *
 * @param event
 * @param deltaTime
 * @param time
 * @param running
 * @param renderer
 */
void EventManager::handleDialogEvent(SDL_Event* event, float deltaTime,
                                     float time, bool* running,
                                     SDL_Renderer* renderer) {
  // Keyboard input that trigger dialogs
  switch (event->key.keysym.sym) {
    case SDLK_e:
    case SDLK_SPACE:
      dialogManager.clearDialog();
      break;
  }

  // Switch back to game mode or continue displaying the rest of the dialogs
  if (!dialogManager.check()) {
    isDialog = false;
    displayGame();
  } else {
    std::vector<std::string> dialogList = dialogManager.getDialog();
    showDialog(dialogList[0].c_str(), dialogList[1].c_str());
  }
}

/**
 * @brief Display a series of dialogs on the screen
 *
 * @param names
 * @param texts
 */
void EventManager::displayDialog(std::vector<std::string> names,
                                 std::vector<std::string> texts) {
  dialogManager.handleDialog(names, texts);
  std::vector<std::string> dialog_list = dialogManager.getDialog();

  showDialog(dialog_list[0].c_str(), dialog_list[1].c_str());
}

/**
 * @brief Display a single dialog on the screen
 *
 * @param name
 * @param text
 */
void EventManager::displayDialog(std::string name, std::string text) {
  dialogManager.handleDialog(name, text);
  std::vector<std::string> dialog_list = dialogManager.getDialog();

  showDialog(dialog_list[0].c_str(), dialog_list[1].c_str());
}

/**
 * @brief Moves and draws the main character on the screen
 *
 * @param deltaTime
 * @param direction
 * @param renderer
 */
void EventManager::playerMovement(float deltaTime, direction direction,
                                  SDL_Renderer* renderer) {
  mainActor.move(direction, deltaTime, curRoom.entityList);
  mainActor.collisionDetection(direction, curRoom.entityList);
  curDir = direction;
}

/**
 * @brief Handles player interaction with items
 *
 */
void EventManager::playerInteraction() {
  // interact returns entity only if character is colliding with an object
  // if (mainActor.collision(curRoom.entityList)) mainActor.interact();
  // otherwise do nothing

  // Get current info
  std::string object = mainActor.interact(curRoom.entityList);
  std::cout << "object: " << object << std::endl;
  std::string item(inventory.getSelectedItem());
  std::cout << "item: " << item << std::endl;
  std::cout << "current state: " << stateMonitor.currentState << std::endl;

  // retrieve dialog
  int id = curDialog.triggerDialog(mainActor.position, object, item,
                                   stateMonitor.currentState);
  std::cout << "id: " << id << std::endl;

  // if no corresponding dialog is found
  if (id < 0) {
    // if used the wrong item, display "I can't use it here"
    if (object.size() > 0 && item.size() > 0) {
      isDialog = true;
      std::vector<std::string> temp_name = {"Me"};
      std::vector<std::string> temp_dialog = {"I can't use it here."};
      displayDialog(temp_name, temp_dialog);
    }
    return;
  }

  dialog* d = &(curDialog.dialogList[id]);

  // play sound
  audioView->playSound("interact");

  isDialog = true;

  // Inventory Update and trigger dialog
  if (item != "hands") inventory.removeItem();
  if (d->pickItem.size() > 0) {
    if (!(inventory.itemHasBeenUsed(d->pickItem) ||
          inventory.itemInInventory(
              d->pickItem))) {  // If you successfully pick up an
                                // item, play the normal dialog
      displayDialog(d->speakers, d->texts);
      inventory.addItem(d->pickItem);
    } else {  // If you already picked up the item, play default dialog
      std::vector<std::string> temp_name = {"Me"};
      std::vector<std::string> temp_dialog = {
          "I don't think I can find anything else here."};
      displayDialog(temp_name, temp_dialog);
    }
  } else {
    displayDialog(d->speakers, d->texts);  // display dialogs
  }

  // State transision
  int switchToRoom = 0;
  if (d->transitToState.size() > 0) {
    switchToRoom = stateMonitor.update(d->transitToState);
  }

  // std::cout << "transit to state: " << d->transitToState << std::endl;

  // handle doors/winning/penalties
  if (switchToRoom == 1) {
    roomChange(Rooms::bedroom);
  } else if (switchToRoom == 2) {
    audioView->playSound("door");
    roomChange(Rooms::kitchen);
  } else if (switchToRoom == 3) {
    audioView->playSound("door");
    roomChange(Rooms::bathroom);
  } else if (switchToRoom == 4) {
    audioView->playSound("door");
    roomChange(Rooms::foyer);
  } else if (switchToRoom == 5) {
    inventory
        .resetInventory();  // Resets the inventory when you enter the hallway
    audioView->playSound("door");
    roomChange(Rooms::hallway);
  } else if (switchToRoom == 6) {
    clock.deductTime();  // penalty
  } else if (switchToRoom == 7) {
    gameStarted = false;
    this->winScreen();  // winning
  }
}

/**
 * @brief Pause event
 *
 * @param time
 */
void EventManager::pauseGame(float time) {
  isPaused = true;
  gameView->drawPauseMenu();
  gameView->presentScreen();
}

/**
 * @brief Present start screen
 *
 */
void EventManager::startScreen(void) {
  audioView->playMusic("main");
  gameView->drawStartScreen();
  gameView->presentScreen();
}

/**
 * @brief Losing event
 *
 */
void EventManager::loseScreen(void) {
  gameView->drawLosingScreen();
  gameView->presentScreen();
}

/**
 * @brief Winning event
 *
 */
void EventManager::winScreen(void) {
  audioView->playMusic("win");
  gameView->drawWinningScreen();
  gameView->presentScreen();
}

/**
 * @brief Handles start game event
 *
 */
void EventManager::startGame(void) {
  clock.start();
  audioView->playMusic("main");
  inventory.resetInventory();
  roomChange(Rooms::bedroom);
  // startScreen();
}

/**
 * @brief Handles room changes
 *
 * @param r : type of room to change to
 */
void EventManager::roomChange(Rooms r) {
  // reset room type
  curRoom = Room(r);
  currRoomName = r;
  // reset dialog
  curDialog = Dialog(r);
  // reset player's born point and movement boundary
  mainActor.position.x = curRoom.bornX;
  mainActor.position.y = curRoom.bornY;
  mainActor.setBoundary(curRoom.boundX, curRoom.boundY, curRoom.boundW,
                        curRoom.boundH);

  // Since the hallway has multiple doors, we need to account for which door the
  // player just left
  if (stateMonitor.currentState == "h1") {  // Bedroom door
    mainActor.position.x = 154;
    mainActor.position.y = 616;
  } else if (stateMonitor.currentState == "h2") {  // Kitchen door
    mainActor.position.x = 439.5;
    mainActor.position.y = 296.5;
  } else if (stateMonitor.currentState == "h3") {  // Bathroom door
    mainActor.position.x = 812;
    mainActor.position.y = 175;
  }

  // DEBUG:
  std::string s;
  switch (r) {
    case Rooms::kitchen:
      s = "k1";
      break;
    case Rooms::bathroom:
      s = "b1";
      break;
    case Rooms::bedroom:
      s = "e1";
      break;

    default:
      break;
  }

  // Show the first dialog when player enters the room
  isDialog = true;
  displayDialog(curDialog.dialogList[0].speakers,
                curDialog.dialogList[0].texts);
  if (s.size() > 0) stateMonitor.update(s);
}

/**
 * @brief Resume game event
 *
 */
void EventManager::returnToGame(void) {
  isPaused = false;
  std::cout << "resume game" << std::endl;

  displayGame();
}

/**
 * @brief Inventory item selection change event
 *
 */
void EventManager::inventoryChange() { inventory.changeSelectedItem(); }

/**
 * @brief Exit game event
 *
 * @param event
 * @param time
 * @param running
 */
void EventManager::exitEvent(SDL_Event* event, float time, bool* running) {
  *running = false;
}

/**
 * @brief Display all elements of the game to the screen
 *
 */
void EventManager::displayGame() {
  gameView->clearScreen();
  gameView->displayTime(clock.getCurTime());
  gameView->drawUI();
  gameView->drawInventory(inventory.currentPosition + 1);
  gameView->drawItems(&inventory);
  gameView->drawRoom(&curRoom);
  gameView->drawActor(mainActor.position, mainActor.size, curDir);
  gameView->roomToPosition();
  // debug
  if (showEntity) gameView->drawEntities(&curRoom);
  gameView->presentScreen();
}

/**
 * @brief Display dialog on screen
 *
 * @param name
 * @param text
 */
void EventManager::showDialog(const char* name, const char* text) {
  gameView->clearScreen();
  gameView->displayTime(clock.getCurTime());
  gameView->drawUI();
  gameView->drawInventory(curItem + 1);
  gameView->drawItems(&inventory);
  gameView->drawRoom(&this->curRoom);
  gameView->drawActor(mainActor.position, mainActor.size, curDir);
  gameView->roomToPosition();

  gameView->drawDialog(text, name);
  gameView->presentScreen();
}
