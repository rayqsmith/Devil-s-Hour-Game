#ifndef _SPEECHBOX_H_
#define _SPEECHBOX_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdlib.h>

#include <iostream>
#include <vector>

#include "constants.h"
#include "vec2d.h"

static SDL_Color white = {255, 255, 255, 255};
#define FONT_SIZE 20
#define FONT_TEXTURE_SIZE 512
#define NUM_CHAR 128
#define MAX_WORD_LENGTH 32
#define MAX_LINE_LENGTH 1024

struct glyph {
  SDL_Texture *char_image;
  int w, h;
};

class SpeechBox {
 public:
  std::vector<glyph> glyphs;
  SDL_Renderer *renderer;
  TTF_Font *font;
  SDL_Rect dialogBoxRect;

  SpeechBox(){};
  SpeechBox(SDL_Renderer *renderer) { this->renderer = renderer; };

  void initGlyph();
  void drawText(const char *text, int x, int y, int maxWidth);
  void textDimensions(const char *text, int *w, int *h);
  int getWrappedTextHeight(const char *text, int maxWidth);
  int drawTextWrapped(const char *text, int x, int y, int maxWidth,
                      bool toScreen = true);
  void drawTextLine(const char *text, int x, int y);

  void initFonts(const char *font_name);

  void fillArray(char arr[], int max, char value);
  void drawDialogBox(void);
};
#endif
