#ifndef _COMPUTER_H_INCLUDED
#define _COMPUTER_H_INCLUDED

#include <SDL2/SDL.h>

#define COMPUTER_IMAGE "computer.png"

typedef struct {
	int health;
	int healthTotal;
	SDL_Texture* texture;
	SDL_Rect pos;
} Computer; 

void computerInit(Computer* computer, int healthTotal, SDL_Rect pos, SDL_Renderer* renderer);
void computerFree(Computer* computer);
void computerRender(Computer* computer, Display* display);

#endif
