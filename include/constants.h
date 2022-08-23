#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include <SDL.h>

#include <vector>

#include "vec2d.h"

enum class Rooms { bedroom, bathroom, kitchen, foyer, hallway };
enum class PauseSelection { none, resume, exit };

static SDL_Color WHITE = {255, 255, 255, 255};
static SDL_Color SILVER = {192, 192, 192};
static SDL_Color BLACK = {0, 0, 0};

// Dialog Box position constants
// Text positioning
static Vec2d dialogPosition(355, 510);
static int dialogWidth = 1014;

// dialog box
static Vec2d dialogBoxPosition(335, 500);
static Vec2d dialogBoxSize(1019, 263);

enum class direction { UP, DOWN, LEFT, RIGHT };
static int SCREEN_WIDTH = 1400;
static int SCREEN_HEIGHT = 800;

#endif /* _CONSTANTS_H_ */