#ifndef _HERO_H_INCLUDED
#define _HERO_H_INCLUDED

#include <stdbool.h>
#include <SDL2/SDL.h>

#define HERO_LEFT_IMAGE "left.png"
#define HERO_RIGHT_IMAGE "right.png"

#define JUMP_SPEED -15
#define MOVEMENT_SPEED 8
#define HERO_GRAVITY 0.4

typedef struct {
	SDL_Texture* textureLeft;
	SDL_Texture* textureRight;
	SDL_Rect pos;
	float posX, posY;
	float speedX, speedY;
	bool isJumping;
	bool isFacingLeft;
} Hero;

void heroInit(Hero* hero, SDL_Rect pos, SDL_Renderer* renderer);
void heroFree(Hero* hero);
void heroRender(Hero* hero, Display* display);
void heroUpdate(Hero* hero);
void heroJump(Hero* hero);
void heroLeft(Hero* hero);
void heroRight(Hero* hero);
void heroStopLeft(Hero* hero);
void heroStopRight(Hero* hero);


#endif
