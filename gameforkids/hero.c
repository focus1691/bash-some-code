#include <string.h>
#include "display.h"
#include "hero.h"

void heroInit(Hero* hero, SDL_Rect pos, SDL_Renderer* renderer) {
	hero->textureLeft = loadTexture(renderer, HERO_LEFT_IMAGE);
	hero->textureRight = loadTexture(renderer, HERO_RIGHT_IMAGE);
	memcpy(&hero->pos, &pos, sizeof(pos));
	hero->posX = pos.x;
	hero->posY = pos.y;
	hero->speedX = 0;
	hero->speedY = 0;
	hero->isJumping = false;
	hero->isFacingLeft = true;
}

void heroFree(Hero* hero) {
	SDL_DestroyTexture(hero->textureLeft);
	SDL_DestroyTexture(hero->textureRight);
}

void heroRender(Hero* hero, Display* display) {
	SDL_Texture* toRender;
	if(hero->isFacingLeft) {
		toRender = hero->textureLeft;
	} else {
		toRender = hero->textureRight;
	}

	SDL_RenderCopy(display->renderer, toRender, NULL, &hero->pos);
}

void heroUpdate(Hero* hero) {
	hero->posX += hero->speedX;
	hero->posY += hero->speedY;
	if(hero->posX < 0) {
		hero->posX = 0;
	}

	if(hero->posY < 0) {
		hero->posY = 0;
	}

	if(hero->posX + hero->pos.w > WINDOW_WIDTH) {
		hero->posX = WINDOW_WIDTH - hero->pos.w;
	}

	if(hero->posY + hero->pos.h > WINDOW_HEIGHT) {
		hero->posY = WINDOW_HEIGHT - hero->pos.h;
		hero->isJumping = false;
	}

	if(hero->isJumping) {
		hero->speedY += HERO_GRAVITY;
	}

	hero->pos.x = hero->posX;
	hero->pos.y = hero->posY;
}

void heroJump(Hero* hero) {
	if(!hero->isJumping) {
		hero->isJumping = true;
		hero->speedY = JUMP_SPEED;
	}
}

void heroLeft(Hero* hero) {
	hero->isFacingLeft = true;
	hero->speedX = -MOVEMENT_SPEED;
}

void heroRight(Hero* hero) {
	hero->isFacingLeft = false;
	hero->speedX = MOVEMENT_SPEED;
}

void heroStopLeft(Hero* hero) {
	if(hero->speedX < 0) {
		hero->speedX = 0;
	}
}

void heroStopRight(Hero* hero) {
	if(hero->speedX > 0) {
		hero->speedX = 0;
	}
}
