#include <stdio.h>
#include <SDL2/SDL.h>

#include "sdlHelper.h"
#include "directoryItem.h"
#include "state.h"

int main(int argc, char** args) {
	if(!initSDL()) {
		printf("Initialization failed\n");
    return 1;
	}

  char quit = 0;
  SDL_Event event;

	struct State currentState = initState();
	updateSDL(&currentState);

  while(!quit) {
    while(SDL_PollEvent(&event) != 0) {
      if(event.type == SDL_QUIT) {
        quit = 1;
      }
			/*else if (event.type == SDL_MOUSEBUTTONUP && event.clicks == 2) {
				directoryItemDoubleClicked(&(currentState.directoryContents), event.x, event.y);
			}*/
    }
  }

	closeSDL();
	freeState(&currentState);

	return 0;
}
