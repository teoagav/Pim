#include <stdio.h>
#include <SDL2/SDL.h>

#include "sdlHelper.h"
#include "fileManipulation.h"

int main(int argc, char** args) {
	if(!initSDL()) {
		printf("Initialization failed\n");
    return 1;
	}

  char quit = 0;
  SDL_Event event;

	struct DIRECTORY currentDir = listDirectoryItems(".");
	updateSDL(&currentDir);

  while(!quit) {
    while(SDL_PollEvent(&event) != 0) {
      if(event.type == SDL_QUIT) {
        quit = 1;
      }
    }
  }

	closeSDL();
	freeDirectory(currentDir);

	return 0;
}
