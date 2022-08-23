// Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>

#include <iostream>

#include "eventManager.h"
#include "room.h"

// Screen dimension constants
// static const int SCREEN_WIDTH = 1024;
// static const int SCREEN_HEIGHT = 768;

// Room enummerations
enum rooms { Front_Foyer, Bedroom, Bathroom, Kitchen, Hallway };

void csci437_error(const std::string& msg) {
  std::cerr << msg << " (" << SDL_GetError() << ")" << std::endl;
  exit(0);
}

void csci437_img_error(const std::string& msg) {
  std::cerr << msg << " (" << IMG_GetError() << ")" << std::endl;
  exit(0);
}
SDL_Surface* load_bitmap(SDL_Surface* input) {
  // Load bitmap
  if (input == NULL) csci437_img_error("Could not image!");
  return input;
}

SDL_Texture* convert_image_to_texture(SDL_Renderer* renderer,
                                      SDL_Surface* image) {
  // convert to texture
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
  if (texture == NULL) csci437_error("Could not create texture from surface!");

  // delete image
  SDL_FreeSurface(image);
  image = NULL;

  return texture;
}

int main(int argc, char** argv) {
  /*** Initialization ***/

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    csci437_error("SDL could not initialize!");

  // Create window
  SDL_Window* window = SDL_CreateWindow("Devil's Hour", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                        SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) csci437_error("Window could not be created!");

  // Init Bitmap loading
  if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0)
    csci437_img_error("SDL could not initialize bitmap loaders!");

  // Initialize SDL_mixer
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    csci437_img_error("SDL_mixer could not initialize! SDL_mixer Error");
  }

  // Small delay to allow the system to create the window.
  SDL_Delay(100);

  // Create renderer
  SDL_Renderer* renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) csci437_error("Unable to create renderer!");

  /*** Main Loop ***/
  bool running = true;
  bool start = false;
  bool eventHappened = false;

  int inactivityCount = 0;

  GameView gameView = GameView(renderer);
  AudioView audioView = AudioView();
  audioView.loadMedia();
  // audioView.playMusic();
  audioView.playSound("door");
  EventManager eventManager(&gameView, &audioView);
  SDL_Event e;
  Rooms current_room;
  current_room = Rooms::bedroom;
  float deltaTime = 0.0f;
  uint32_t startTime, endTime;
  Uint16 current_time = 0;
  eventManager.startGame();

  // create the update time event
  Uint32 updateClockevent = SDL_RegisterEvents(1);
  SDL_Event no_event;
  no_event.type = updateClockevent;

  // While application is running
  while (running) {
    // loop start time
    startTime = SDL_GetTicks();
    eventHappened = false;

    // Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
      inactivityCount = 0;

      // gameView.clearScreen();

      // gameView.drawUI();
      // gameView.drawInventory(eventManager.curItem + 1);
      // gameView.drawRoom(room);
      // gameView.drawActor(eventManager.mainActor.position,
      //  eventManager.mainActor.size, eventManager.curDir);

      eventManager.handle_event(&e, deltaTime, startTime, &running, renderer);
      eventHappened = true;

      // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      // SDL_RenderClear(renderer);
      // SDL_SetTextureColorMod(texture, red * 255, green * 255, blue *
      // 255);
      // SDL_RenderCopy(renderer, roomTx, NULL, &dst);
      // SDL_RenderPresent(renderer);

      endTime = SDL_GetTicks();
      deltaTime = (endTime - startTime) / 1.0f;
    }

    if (!eventHappened) {
      inactivityCount++;
      if (inactivityCount == 500) SDL_PushEvent(&no_event);
    }
  }
  // Gets end time of the loop
  Uint32 end_time = SDL_GetTicks();

  /*** Clean Up ***/

  // Destroy audio
  audioView.close();

  // Destroy texture
  // SDL_DestroyTexture(roomTx);

  // Destroy renderer
  SDL_DestroyRenderer(renderer);

  // Destroy window
  SDL_DestroyWindow(window);

  // Quit SDL subsystems
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();

  // Done.
  return 0;
}
