#include "audioView.h"

#include <iostream>

/**
 * @brief Construct a new Audio View:: Audio View object
 * 
 */
AudioView::AudioView() {
  // Game music
  gMainMusic = NULL;
  gWinMusic = NULL;

  // Game sounds
  gInteract = NULL;
  gDoor = NULL;
}

/**
 * @brief Load media files
 * 
 */
void AudioView::loadMedia() {
  // Load music
  gMainMusic = Mix_LoadMUS("../resource/audio/bg_music.mp3");
  if (gMainMusic == NULL) {
    printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
  }

  gWinMusic = Mix_LoadMUS("../resource/audio/microfrog.wav");
  if (gWinMusic == NULL) {
    printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
  }

  // Load sound effects
  gInteract = Mix_LoadWAV("../resource/audio/interact.wav");
  if (gInteract == NULL) {
    printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
  }

  gDoor = Mix_LoadWAV("../resource/audio/open_door.wav");
  if (gDoor == NULL) {
    printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
  }
}

/**
 * @brief Cleanup
 * 
 */
void AudioView::close() {
  // Free the music
  Mix_FreeMusic(gMainMusic);
  Mix_FreeMusic(gWinMusic);
  gMainMusic = NULL;
  gWinMusic = NULL;

  // Free the sounds

  Mix_FreeChunk(gInteract);
  Mix_FreeChunk(gDoor);
  gInteract = NULL;
  gDoor = NULL;

  // Quit SDL music subsystem
  Mix_Quit();
}

/**
 * @brief Play specified sound
 * 
 * @param soundName 
 */
void AudioView::playSound(std::string soundName) {
  if (soundName == "interact") {
    Mix_PlayChannel(-1, gInteract, 0);
  } else if (soundName == "door") {
    Mix_PlayChannel(-1, gDoor, 0);
  } else {
    Mix_PlayChannel(-1, gInteract, 0);
  }
}

/**
 * @brief Play specified music
 * 
 * @param musicName 
 */
void AudioView::playMusic(std::string musicName) {
  if (musicName == "main")
    Mix_PlayMusic(gMainMusic, -1);
  else if (musicName == "win")
    Mix_PlayMusic(gWinMusic, -1);
}