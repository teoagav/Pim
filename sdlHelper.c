#include "sdlHelper.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "GUIConstants.h"

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
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
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

void drawText(const char* text, const size_t nameLength, const int xPos,const int yPos) {
	SDL_Color textColor = { 0, 0, 0 };
	SDL_Surface* textSurface = NULL;
	SDL_Texture* textTexture = NULL;

	if (!(textSurface = TTF_RenderText_Solid(fileTextFont, text, textColor))) {
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else if (!(textTexture = SDL_CreateTextureFromSurface(renderer, textSurface))) {
		printf("Unable to create texture from rendered text! Error: %s\n", SDL_GetError());
	}
	else {
		const int offset = FILE_LIST_LEFT_PADDING + FILE_ICON_SIZE + FILE_TEXT_ICON_GAP;
		SDL_Rect renderQuad  = { offset, yPos, nameLength*CHAR_WIDTH, FILE_TEXT_HEIGHT };

		if (SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad)) {
			printf("Render copy for writing text failed\n");
		}

		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(textTexture);
		textSurface = NULL;
		textTexture = NULL;
	}
}

void drawRectOutLine(const int xPos, const int yPos, const int width, const int height) {
	const SDL_Point points[5] = {{xPos, yPos}, {xPos + width, yPos}, {xPos + width, yPos + height}, {xPos, yPos + height}, {xPos, yPos}};
	if (SDL_RenderDrawLines(renderer, points, 5)) {
		printf("Render draw sqaure outline failed. Error: %s\n", SDL_GetError());
	}
}

void drawFolder(const int xPos, const int yPos) {
	SDL_Rect renderQuad = { xPos, yPos, FILE_ICON_SIZE, FILE_ICON_SIZE };

	if (SDL_RenderCopy(renderer, folderTexture, NULL, &renderQuad)) {
		printf("Render copy for folder icon failed\n");
	}
}

void drawFile(const int xPos, const int yPos) {
	SDL_Rect renderQuad  = { xPos, yPos, FILE_ICON_SIZE, FILE_ICON_SIZE };

	if (SDL_RenderCopy(renderer, fileTexture, NULL, &renderQuad)) {
		printf("Render copy for file icon failed\n");
	}
}

//TODO add struct for current directory bar and add it to state
void drawCurrentDirectoryBar(const char* currentDirectory, const size_t length) {
	const int width = SCREEN_WIDTH - FILE_LIST_LEFT_PADDING - FILE_LIST_RIGHT_PADDING;
	drawRectOutLine(FILE_LIST_LEFT_PADDING, CURRENT_DIRECTORY_TOP_PADDING, width, CURRENT_DIRECTORY_BAR_HEIGHT);
	drawText(currentDirectory, length, FILE_LIST_LEFT_PADDING, CURRENT_DIRECTORY_TOP_PADDING + TEXT_TOP_OFFSET);
}

void updateSDL(struct State* state) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);

	drawDirectoryItems(state->directoryContents);
	drawCurrentDirectoryBar(state->currentDirectory, state->cdStringLength);

	SDL_RenderPresent(renderer);
}

void clearSDL() {
	SDL_RenderClear(renderer);
}

void presentSDL() {
	SDL_RenderPresent(renderer);
}
