#include <stdio.h>
#include <SDL2/SDL.h>

#include "sdlHelper.h"

int main(int argc, char** args) {
	if(!initSDL()) {
    return 1;
	}

  char quit = 0;
  SDL_Event event;

  while(!quit) {
    while(SDL_PollEvent(&event) != 0) {
      if(event.type == SDL_QUIT) {
        quit = 1;
      }
    }

    updateSDL();
  }

	closeSDL();

	return 0;
}
