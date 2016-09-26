#include <string.h>
#include "display.h"
#include "computer.h"

void computerInit(Computer* computer, int healthTotal, SDL_Rect pos, SDL_Renderer* renderer) {
	computer->texture = loadTexture(renderer, COMPUTER_IMAGE);
	computer->healthTotal = healthTotal;
	computer->health = healthTotal;
	memcpy(&computer->pos, &pos, sizeof(pos));
}

void computerFree(Computer* computer) {
	SDL_DestroyTexture(computer->texture);
}

void computerRender(Computer* computer, Display* display) {
	SDL_Rect hp;
	hp.x = computer->pos.x + 10;
	hp.y = computer->pos.y - computer->pos.h / 10;;
	hp.w = (computer->pos.w - 20) * (float)computer->health / (float)computer->healthTotal;
	hp.h = computer->pos.h / 10;
	SDL_RenderCopy(display->renderer, computer->texture, NULL, &computer->pos);
	SDL_SetRenderDrawColor(display->renderer, 255, 0, 0, 0);
	SDL_RenderFillRect(display->renderer, &hp);
}
