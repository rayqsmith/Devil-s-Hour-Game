
#include "speechBox.h"

// inline array to init a array of 0's
inline void SpeechBox::fillArray(char arr[], int max, char value) {
  for (int i = 0; i < max; i++) {
    arr[i] = value;
  }
}

// Loads the font file
void SpeechBox::initFonts(const char *font_name) {
  TTF_Init();
  this->font = TTF_OpenFont(font_name, FONT_SIZE);
}

// takes characters and add it to a glyph(vector of  textures)
void SpeechBox::initGlyph() {
  SDL_Surface *surface, *text;
  SDL_Rect dest;
  int i;
  char temp_char[2];
  SDL_Rect *g;
  glyph temp;
  int w, h;

  surface = SDL_CreateRGBSurface(0, FONT_TEXTURE_SIZE, FONT_TEXTURE_SIZE, 32, 0,
                                 0, 0, 0xff);
  SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGBA(surface->format, 0, 0, 0, 0));

  dest.x = 0;
  dest.y = 0;

  for (int iter = 0; iter <= 'z'; iter++) {
    temp_char[0] = iter;
    temp_char[1] = 0;

    text = TTF_RenderUTF8_Blended(this->font, temp_char, white);
    TTF_SizeText(this->font, temp_char, &dest.w, &dest.h);
    temp.char_image = SDL_CreateTextureFromSurface(renderer, text);
    SDL_QueryTexture(temp.char_image, NULL, NULL, &w, &h);
    temp.h = h;
    temp.w = w;
    glyphs.push_back(temp);
  }
}

// draw the text to the screen
void SpeechBox::drawText(const char *text, int x, int y, int maxWidth) {
  if (maxWidth > 0) {
    drawTextWrapped(text, x, y, maxWidth);
  } else {
    drawTextLine(text, x, y);
  }
}

// draw a single line of text
void SpeechBox::drawTextLine(const char *text, int x, int y) {
  int i, character;
  SDL_Rect dest;
  glyph glyph;
  i = 0;
  character = text[i++];

  while (character) {
    glyph = this->glyphs.at(character);

    dest.x = x;
    dest.y = y;
    dest.w = glyph.w;
    dest.h = glyph.h;
    SDL_RenderCopy(this->renderer, glyph.char_image, NULL, &dest);
    x += glyph.w;
    character = text[i++];
  }
}

// draw multiline text to fit the box
int SpeechBox::drawTextWrapped(const char *text, int x, int y, int maxWidth,
                               bool toScreen) {
  char word[MAX_WORD_LENGTH], line[MAX_LINE_LENGTH];
  int word_iter, text_iter, wordWidth, lineWidth, character, textLength;
  int space = (int)' ';
  bool draw = true;

  // inits the line and word empty arrays
  text_iter = 0;
  fillArray(word, MAX_WORD_LENGTH, 0);
  fillArray(line, MAX_LINE_LENGTH, 0);

  word_iter = 0;
  lineWidth = 0;
  wordWidth = 0;
  textLength = strlen(text);
  character = text[text_iter++];

  // takes each character in the string
  while (character) {
    // adds the character draw width to the total word width;
    wordWidth += this->glyphs.at(character).w;
    // if not space add the character to the word
    if (character != space) {
      word[word_iter++] = character;
    }
    // if end of word or text is done
    if (character == space || text_iter == textLength) {
      // if line is over the max with the space
      if (lineWidth + wordWidth >= maxWidth) {
        // Draw text line
        if (toScreen) {
          drawTextLine(line, x, y);
        }
        // Clear line, sets the location of next line y
        fillArray(line, MAX_LINE_LENGTH, 0);
        y += glyphs.at(space).h;
        lineWidth = 0;
      }
      // if line is not new, add the space
      else if (lineWidth != 0) {
        strcat(line, " ");
      }
      // add word to the line
      strcat(line, word);
      lineWidth += wordWidth;
      fillArray(word, MAX_WORD_LENGTH, 0);
      wordWidth = 0;
      word_iter = 0;
    }
    character = text[text_iter++];
  }
  // draw the line
  if (toScreen) {
    drawTextLine(line, x, y);
  }

  // gets the height of the glyph
  return y + glyphs.at(space).h;
}

// gets the dimensions of the text to set the boc
void SpeechBox::textDimensions(const char *text, int *w, int *h) {
  int i, character;
  glyph g;
  *w = 0;
  *h = 0;
  i = 0;

  character = text[i++];

  while (character) {
    g = glyphs.at(character);
    *w += g.w;
    *h = std::max(g.h, *h);
    character = text[i++];
  }
}

int SpeechBox::getWrappedTextHeight(const char *text, int maxWidth) {
  return drawTextWrapped(text, 0, 0, maxWidth, false);
}

// draws the dialog box to the screen
void SpeechBox::drawDialogBox(void) {
  // surface from imagae
  SDL_Surface *dialogBoxImage = IMG_Load("../resource/ui/dialog_box.png");

  dialogBoxRect.x = dialogBoxPosition.x;
  dialogBoxRect.y = dialogBoxPosition.y;
  dialogBoxRect.w = dialogBoxSize.x;
  dialogBoxRect.h = dialogBoxSize.y;

  SDL_Texture *dialogBox =
      SDL_CreateTextureFromSurface(this->renderer, dialogBoxImage);
  // copy to renderer
  SDL_RenderCopy(this->renderer, dialogBox, NULL, NULL);
  // destroy surface and texture
  SDL_FreeSurface(dialogBoxImage);
  SDL_DestroyTexture(dialogBox);
}
