// Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include <iostream>

#include "eventManager.h"

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
  if (SDL_Init(SDL_INIT_VIDEO) < 0) csci437_error("SDL could not initialize!");
  TTF_Init();

  // Create window
  SDL_Window* window =
      SDL_CreateWindow("Devil's Hour", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 1400, 800, SDL_WINDOW_SHOWN);
  if (window == NULL) csci437_error("Window could not be created!");

  // Init Bitmap loading
  if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0)
    csci437_img_error("SDL could not initialize bitmap loaders!");

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

  GameView gameView(renderer);
  EventManager eventManager(&gameView);
  SDL_Event e;
  float deltaTime = 0.0f;
  uint32_t startTime, endTime;
  Uint16 current_time = 0;

  eventManager.startScreen();

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
      eventManager.handle_event(&e, deltaTime, startTime, &running, renderer);
      eventHappened = true;
      endTime = SDL_GetTicks();
      deltaTime = (endTime - startTime) / 1.0f;
    }
  }
  // Gets end time of the loop
  Uint32 end_time = SDL_GetTicks();

  /*** Clean Up ***/

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
