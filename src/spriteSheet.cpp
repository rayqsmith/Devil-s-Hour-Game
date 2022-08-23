#include "spriteSheet.h"

/* May be used for a single image 1x1 sprite sheets or for animation 4x4
   row 0: facing towards
   row 1: facing left
   row 2: facing right
   row 3: facing away
*/
// Modify to texture

/* constructor */
SpriteSheet::SpriteSheet() {}

/* Destructor to avoid memory leak*/
SpriteSheet::~SpriteSheet() {
  SDL_FreeSurface(spriteSheetImage);
  spriteSheetImage = NULL;
  SDL_DestroyTexture(spriteTexture);
  spriteTexture = NULL;
}
/* stores the entire sprite image */
void SpriteSheet::storeImage(char const *image_path, int row, int col) {
  spriteSheetImage = IMG_Load(image_path);
  // surface-> sets size dimensions of a frame
  frame_rect.h = spriteSheetImage->h / row;
  frame_rect.w = spriteSheetImage->w / col;
}

/* given the frame's position on the sprite sheet, select the sprite (zero
 * indexing) */
void SpriteSheet::selectSprite(int row, int col) {
  // calculate the coordinate of the top left of selected frame
  frame_rect.x = row * frame_rect.w;
  frame_rect.y = col * frame_rect.h;
}

/* draws a sprite on the renderer given a RECT position */
void SpriteSheet::drawSprite(SDL_Renderer *renderer, SDL_Rect *position) {
  spriteTexture = SDL_CreateTextureFromSurface(renderer, spriteSheetImage);
  SDL_RenderCopy(renderer, spriteTexture, &frame_rect, position);
  // SDL_RenderPresent(renderer);
}
