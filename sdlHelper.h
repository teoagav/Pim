#ifndef _SDL_HELPER_

#define _SDL_HELPER_

#include "fileManipulation.h"

int initSDL();
void updateSDL(struct DIRECTORY* dir);
void clearSDL();
void presentSDL();
void updateSDL();
void closeSDL();

void drawFolder(int yPos);
void drawFile(int yPos);

#endif
