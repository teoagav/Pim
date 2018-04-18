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

	//updateSDL();
	//Hacky print to test out function
	struct DIRECTORY currentDir = listDirectoryItems(".");
	clearSDL();
	printf("%zu\n", currentDir.itemCount);
	for (int i = 0; i < currentDir.itemCount; i++) {
		printf("%s ", currentDir.items[i].name);
		if (currentDir.items[i].type == FILE_TYPE) {
			printf("%d\n", i*30);
			drawFile(i*30);
		} else if (currentDir.items[i].type == FOLDER_TYPE || currentDir.items[i].type == UP_ONE_LEVEL_TYPE) {
			printf("%d\n", i*30);
			drawFolder(i*30);
		}
	}
	presentSDL();

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
