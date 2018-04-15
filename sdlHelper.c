const int SCREEN_WIDTH = 750;
const int SCREEN_HEIGHT = 500;

bool loadMedia();
SDL_Texture* loadTexture(char** path);

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gXOut = NULL;


bool initSDL() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL failed to start. Error: %s\n", SDL_GetError());
		return false;
	}
	else if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" )) {
		printf("Linear texture filtering could not be enabled");
		return false;
	}
	else if ((gWindow = SDL_CreateWindow( "Sea Explorer", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) == NULL) {
		printf("Window failed to be created. Error: %s\n", SDL_GetError());
		return false;
	}
	else if (gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED) == NULL) {
		printf("Renderer failed be created! Error: %s\n", SDL_GetError());
		return false;
	}
	else {
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	}

	return true;
}

SDL_Texture* loadTexture(char** path) {
	SDL_Texture* newTexture = NULL;

	SDL_Surface* tempSurface = loadSurface(path);
	if(tempSurface != NULL) {
    newTexture = SDL_CreateTextureFromSurface(gRenderer, tempSurface);

		if(newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}

		SDL_FreeSurface(tempSurface);
	} else {
		printf("Unable to load surface from %s! SDL Error: %s\n", path, SDL_GetError());
	}

	return newTexture;
}

bool loadMedia() {
	gXOut = loadTexture("file_icon.bmp");
	return gXOut != NULL;
}

void closeSDL() {
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	SDL_Quit();
}

int main( int argc, char* args[] ) {
	if( !init() ) {
		printf( "Failed to initialize!\n" );
	} else {
		if( !loadMedia() ) {
			printf( "Failed to load media!\n" );
		}	else {
			bool quit = false;

			SDL_Event e;

			while( !quit ) {
				while( SDL_PollEvent( &e ) != 0 ) {
					if( e.type == SDL_QUIT ) {
						quit = true;
					}
				}

				SDL_RenderClear( gRenderer );

				SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );

				SDL_RenderPresent( gRenderer );
			}
		}
	}

	close();

	return 0;
}
