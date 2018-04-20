#ifndef _SDL_HELPER_

#define _SDL_HELPER_

#include "state.h"

int initSDL();
void updateSDL(struct State* dir);
void clearSDL();
void presentSDL();
void updateSDL();
void closeSDL();

#endif
