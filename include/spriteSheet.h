#ifndef _SPRITESHEET_H_
#define _SPRITESHEET_H_

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>

class SpriteSheet {
 public:
  /* constructor is given an image and how many rows and columns it has */
  SpriteSheet();
  ~SpriteSheet();

  void storeImage(char const *image_path, int row, int col);
  void selectSprite(int row, int col);
  void drawSprite(SDL_Renderer *renderer, SDL_Rect *position);

 private:
  /* will the partitions within the sprite image */
  SDL_Rect frame_rect;
  /* this surface holds raw pixel data of the entire sprite sheet used */
  SDL_Surface *spriteSheetImage;
  SDL_Texture *spriteTexture;
};

#endif