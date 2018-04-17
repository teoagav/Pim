#include <stdio.h>
#include <SDL2/SDL.h>

#include "sdlHelper.h"
#include "fileManipulation.h"

int main(int argc, char** args) {
	if(!initSDL()) {
    return 1;
	}

  char quit = 0;
  SDL_Event event;

	updateSDL();
	//Hacky print to test out function
	struct DIRECTORY currentDir = listDirectoryItems(".");
	for (size_t i = 0; i < currentDir.itemCount; i++) {
		//printf("%s\n", currentDir.items[i].name);
		if (currentDir.items[i].type == FILE_TYPE) {
			drawFile((i+1)*21);
		} else if (currentDir.items[i].type == FOLDER_TYPE) {
			drawFolder((i+1)*21);
		}
	}

  while(!quit) {
    while(SDL_PollEvent(&event) != 0) {
      if(event.type == SDL_QUIT) {
        quit = 1;
      }
    }

    //updateSDL();
  }

	closeSDL();
	freeDirectory(currentDir);

	return 0;
}
