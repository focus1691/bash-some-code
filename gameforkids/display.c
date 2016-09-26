#include <stdio.h>
#include <stdlib.h>
#include "display.h"

static bool gGraphicsInitialized = false;

void graphicsInit(void) {
	int imgFlags;

	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
		fprintf(stderr, "Failed to initialize SDL_image: %s\n", SDL_GetError());
		exit(1);
	}

	if(TTF_Init() != 0) {
		fprintf(stderr, "Failed to initialize SDL_ttf: %s\n", SDL_GetError());
		exit(1);
	}
	gGraphicsInitialized = true;
}

void displayInit(Display* display, char* windowTitle) {
	if(!gGraphicsInitialized) {
		fprintf(stderr, "Initialise graphics first!\n");
		exit(1);
	}
	display->window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if(display->window == NULL) {
		fprintf(stderr, "Failed to create a window: %s\n", SDL_GetError());
	}
	display->renderer = SDL_CreateRenderer(display->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(display->renderer == NULL) {
		fprintf(stderr, "Failed to create a renderer: %s\n", SDL_GetError());
	}
}

void displayFree(Display* display) {
	SDL_DestroyRenderer(display->renderer);
	SDL_DestroyWindow(display->window);
}

SDL_Texture* loadTexture(SDL_Renderer* renderer, char* path) {
	SDL_Texture *newTexture;
	SDL_Surface *loadedSurface;

	loadedSurface = IMG_Load(path);

	if(loadedSurface == NULL) {
		fprintf(stderr, "Failed to load %s: %s\n", path, SDL_GetError());
		exit(1);
	}

	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);

	if(newTexture == NULL) {
		fprintf(stderr, "Failed to load %s: %s\n", path, SDL_GetError());
		exit(1);
	}
	return newTexture;	
}

SDL_Texture* textTexture(SDL_Renderer* renderer, const char* text, const char* fontName, int size, SDL_Color color) {
	SDL_Texture* result = NULL;
	SDL_Surface* qSurface = NULL;
	TTF_Font* font = TTF_OpenFont(fontName, size);	
	if(font == NULL) {
		fprintf(stderr, "Filed to load font %s\n", fontName);
		exit(1);
	}
	qSurface = TTF_RenderText_Solid(font, text, color);
	if(qSurface == NULL) {
		fprintf(stderr, "Failed to render text: %s\n", SDL_GetError());
		exit(1);
	}
	result = SDL_CreateTextureFromSurface(renderer, qSurface);
	SDL_FreeSurface(qSurface);

	if(result == NULL) {
		fprintf(stderr, "Failed to create texture form surface: %s\n", SDL_GetError());
		exit(1);
	}
	TTF_CloseFont(font);
	return result;
}
