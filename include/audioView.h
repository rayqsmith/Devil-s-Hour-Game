#ifndef _AUDIOVIEW_H_
#define _AUDIOVIEW_H_

#include <SDL_mixer.h>

#include <string>

class AudioView {
 private:
  // Music
  Mix_Music *gMainMusic = NULL;
  Mix_Music *gWinMusic = NULL;

  // Sounds effects
  Mix_Chunk *gInteract = NULL;
  Mix_Chunk *gDoor = NULL;

 public:
  AudioView();      /**< Initializes private variables */
  void loadMedia(); /**< Loads music and sound effects from resource folder */
  void playMusic(std::string musicName); /**< Plays the main game music */
  void close(); /**< free all the SDL stuff and private variables*/
  void playSound(std::string soundName); /**< play a given sound */
};

#endif /* _AUDIOVIEW_H_ */