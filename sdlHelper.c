#include "sdlHelper.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "GUIConstants.h"
#include "directoryItem.h"

const int SCREEN_WIDTH = 750;
const int SCREEN_HEIGHT = 750;

int loadMedia();
SDL_Texture* loadTexture(const char* const path);

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* fileTexture = NULL;
SDL_Texture* folderTexture = NULL;
TTF_Font* fileTextFont = NULL;


int initSDL() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL failed to start. Error: %s\n", SDL_GetError());
		return 0;
	}
	else if (TTF_Init() < 0){
		printf("TTF failed to start. Error: %s\n", SDL_GetError());
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
			printf("Failed to create texture from %s. Error: %s\n", path, SDL_GetError());
		}

		SDL_FreeSurface(tempSurface);
	} else {
		printf("Failed to load surface from %s. Error: %s\n", path, SDL_GetError());
	}

	return newTexture;
}

int loadMedia() {
	if (!(fileTexture = loadTexture("./assets/file_icon.bmp"))) {
		printf("File icon failed to open. Error: %s\n", SDL_GetError());
	}
	if (!(folderTexture = loadTexture("./assets/folder_icon.bmp"))) {
		printf("Folder icon failed to open. Error: %s\n", SDL_GetError());
	}
	if (!(fileTextFont = TTF_OpenFont("./assets/Anonymous.ttf", 10))) {
		printf("Font failed to open. Error: %s\n", TTF_GetError());
	}

	return fileTexture != NULL && folderTexture != NULL && fileTextFont != NULL;
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

void drawDirectoryItemName(char* text, const size_t nameLength, const int yPos) {
	SDL_Color textColor = { 0, 0, 0 };
	SDL_Surface* textSurface = NULL;
	SDL_Texture* textTexture = NULL;

	if (!(textSurface = TTF_RenderText_Solid(fileTextFont, text, textColor))) {
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else if (!(textTexture = SDL_CreateTextureFromSurface(renderer, textSurface))) {
		printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
	}
	else {
		//printf("%zu\n", nameLength);
		const int offset = FILE_LIST_LEFT_PADDING + FILE_ICON_SIZE + FILE_TEXT_ICON_GAP;
		SDL_Rect renderQuad  = { offset, yPos, nameLength*CHAR_WIDTH, FILE_TEXT_HEIGHT };

		if (SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad)) {
			printf("Render copy failed\n");
		}

		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(textTexture);
		textSurface = NULL;
		textTexture = NULL;
	}
}

void drawFolder(const int yPos) {
	SDL_Rect renderQuad = { FILE_LIST_LEFT_PADDING, yPos, FILE_ICON_SIZE, FILE_ICON_SIZE };

	if (SDL_RenderCopy(renderer, folderTexture, NULL, &renderQuad)) {
		printf("Render copy failed\n");
	}
}

void drawFile(const int yPos) {
	SDL_Rect renderQuad  = { FILE_LIST_LEFT_PADDING, yPos, FILE_ICON_SIZE, FILE_ICON_SIZE };

	if (SDL_RenderCopy(renderer, fileTexture, NULL, &renderQuad)) {
		printf("Render copy failed\n");
	}
}

void drawDirectoryItem(struct DIRECTORY* dir) {
	printf("%zu\n", dir->itemCount);

	for (int i = 0; i < dir->itemCount; i++) {
		printf("%s\n", dir->items[i].name);
		const int yPos = (i * (FILE_SPACING + FILE_ICON_SIZE)) + FILE_LIST_TOP_PADDING;

		if (dir->items[i].type == FILE_TYPE) {
			drawFile(yPos);
		}
		else if (dir->items[i].type == FOLDER_TYPE || dir->items[i].type == UP_ONE_LEVEL_TYPE) {
			drawFolder(yPos);
		}
		drawDirectoryItemName(dir->items[i].name, dir->items[i].nameLength, yPos + FILE_TEXT_TOP_OFFSET);
	}
}

void updateSDL(struct State* state) {
	SDL_RenderClear(renderer);

	drawDirectoryItem(&state->directoryContents);

	SDL_RenderPresent(renderer);
}

void clearSDL() {
	SDL_RenderClear(renderer);
}

void presentSDL() {
	SDL_RenderPresent(renderer);
}
