#ifndef _DISPLAY_H_INCLUDED
#define _DISPLAY_H_INCLUDED

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768 
#define MAIN_FONT "Calibri.ttf"

#define WHITE {255, 255, 255, 0}
#define RED {255, 0, 0, 0}

typedef struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
} Display;

void graphicsInit(void);

void displayInit(Display* display, char* windowTitle);
void displayFree(Display* display);
SDL_Texture* loadTexture(SDL_Renderer* renderer, char* path);
SDL_Texture* textTexture(SDL_Renderer* renderer, const char* text, const char* fontName, int size, SDL_Color color);


#endif
