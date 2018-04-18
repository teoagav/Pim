#include "sdlHelper.h"
#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 750;
const int SCREEN_HEIGHT = 750;

int loadMedia();
SDL_Texture* loadTexture(const char* const path);

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* fileTexture = NULL;
SDL_Texture* folderTexture = NULL;


int initSDL() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL failed to start. Error: %s\n", SDL_GetError());
		return 0;
	}
	else if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("Linear texture filtering could not be enabled");
		return 0;
	}
	else if ((window = SDL_CreateWindow("Sea Explorer", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) == NULL) {
		printf("Window failed to be created. Error: %s\n", SDL_GetError());
		return 0;
	}
	else if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
		printf("Renderer failed be created! Error: %s\n", SDL_GetError());
		return 0;
	}
	else {
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	}

	return loadMedia();
}

SDL_Texture* loadTexture(const char* const path) {
	SDL_Texture* newTexture = NULL;

	SDL_Surface* tempSurface = SDL_LoadBMP(path);
	if(tempSurface != NULL) {
    newTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);

		if(newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}

		SDL_FreeSurface(tempSurface);
	} else {
		printf("Unable to load surface from %s! SDL Error: %s\n", path, SDL_GetError());
	}

	return newTexture;
}

int loadMedia() {
	fileTexture = loadTexture("file_icon.bmp");
	folderTexture = loadTexture("folder_icon.bmp");
	return fileTexture != NULL && folderTexture != NULL;
}

void closeSDL() {
	SDL_DestroyTexture(fileTexture);
	fileTexture = NULL;

	SDL_DestroyTexture(folderTexture);
	folderTexture = NULL;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	SDL_Quit();
}


void updateSDL() {
	SDL_RenderClear(renderer);

	//SDL_Rect renderQuad = { 50, 100, 25, 25 };

	//SDL_RenderCopy(renderer, folderTexture, NULL, &renderQuad);

	//SDL_RenderPresent(renderer);
}

void clearSDL() {
	SDL_RenderClear(renderer);
}

void presentSDL() {
	SDL_RenderPresent(renderer);
}

void drawFolder(int yPos) {
	SDL_Rect renderQuad = { 50, yPos, 20, 20 };

	SDL_RenderCopy(renderer, folderTexture, NULL, &renderQuad);
}

void drawFile(int yPos) {
	SDL_Rect renderQuad  = { 50, yPos, 20, 20 };

	if(SDL_RenderCopy(renderer, fileTexture, NULL, &renderQuad)){
		printf("Render copy failed\n");
	}
}
