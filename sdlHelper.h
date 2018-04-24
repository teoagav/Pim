#ifndef _SDL_HELPER_

#define _SDL_HELPER_

#include "state.h"

int initSDL();
void updateSDL(struct STATE* dir);
void clearSDL();
void presentSDL();
void updateSDL();
void closeSDL();

void drawRectOutLine(const int xPos, const int yPos, const int width, const int height);
void drawFolder(const int xPos, const int yPos);
void drawFile(const int xPos, const int yPos);
void drawText(const char* text, const size_t nameLength, const int xPos,const int yPos);

#endif
