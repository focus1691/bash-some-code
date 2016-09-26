#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "answers.h"

#define MAX_NUMBER_LENGTH 32
#define ANSWER_FONT_SIZE 300
#define ANSWER_SPEED_RANGE 1.0

void updateLinear(Answer* answer);
void updateGravityRight(Answer* answer);
void updateGravityLeft(Answer* answer);
void updateGravityDown(Answer* answer);
void updateRandomised(Answer* answer);

void answerChoosePattern(Answer* answer);

void answerInit(Answer* answer, int value, bool isCorrect, SDL_Rect pos, SDL_Renderer* renderer) {
	SDL_Color answerTextColor = WHITE;
	SDL_Rect textSize = {0, 40, 600, 150};
	TTF_Font* font;
	char number[MAX_NUMBER_LENGTH];
	SDL_Surface* virus;
	SDL_Surface* text;

	answer->isCorrect = isCorrect;
	answer->isAlive = true;
	memcpy(&answer->pos, &pos, sizeof(pos));

	answer->speedX = rand() * ANSWER_SPEED_RANGE / RAND_MAX - 2*ANSWER_SPEED_RANGE;
	answer->speedY = rand() * ANSWER_SPEED_RANGE / RAND_MAX - 2*ANSWER_SPEED_RANGE;
	answer->posX = pos.x;
	answer->posY = pos.y;
	answerChoosePattern(answer);
	sprintf(number, "%d", value);
	virus = IMG_Load(VIRUS_IMAGE);
	if(virus == NULL) {
		fprintf(stderr, "Failed to load %s\n", VIRUS_IMAGE);
		exit(1);
	}
	font = TTF_OpenFont(MAIN_FONT, ANSWER_FONT_SIZE);
	if(font == NULL) {
		fprintf(stderr, "Failed to load %s\n", MAIN_FONT);
		exit(1);
	}
	text = TTF_RenderText_Solid(font, number, answerTextColor);
	SDL_BlitSurface(text, NULL, virus, &textSize);
	answer->texture = SDL_CreateTextureFromSurface(renderer, virus);
	SDL_FreeSurface(virus);
	SDL_FreeSurface(text);
	TTF_CloseFont(font);
}

void answerUpdate(Answer* answer) {
	answer->updateFunc(answer);
}

void answerRender(Display* display, Answer* answer) {
	if(answer->posX < 0) {
		answer->posX = 0;
		answer->speedX = -answer->speedX;
	}

	if(answer->posY < 0) {
		answer->posY = 0;
		answer->speedY = -answer->speedY;
	}

	if(answer->posX + answer->pos.w > WINDOW_WIDTH) {
		answer->posX = WINDOW_WIDTH - answer->pos.w;
		answer->speedX = -answer->speedX;
	}
	
	if(answer->posY + answer->pos.h > WINDOW_HEIGHT) {
		answer->posY = WINDOW_HEIGHT - answer->pos.h;
		answer->speedY = -answer->speedY;
	}
	answer->pos.x = (int)answer->posX;
	answer->pos.y = (int)answer->posY;

	SDL_RenderCopy(display->renderer, answer->texture, NULL, &answer->pos);
}

void answerFree(Answer* answer) {
	SDL_DestroyTexture(answer->texture);
}

SDL_Rect getPos(void) {
	static int posIndex;
	SDL_Rect pos[] = {
		{700, 100, 52, 52},
		{200, 120, 52, 52},
		{300, 200, 52, 52},
		{450, 500, 52, 52},
		{150, 400, 52, 52},
		{450, 330, 52, 52},
		{910, 200, 52, 52},
		{450, 500, 52, 52},
		{900, 400, 52, 52},
		{280, 440, 52, 52},
		{50, 610, 52, 52},
		{650, 50, 52, 52},
		{150, 100, 52, 52},
		{450, 500, 52, 52},
		{50, 710, 52, 52},
		{450, 500, 52, 52},
		{940, 400, 52, 52},
		{450, 470, 52, 52},
		{750, 180, 52, 52},
		{450, 630, 52, 52},
		{450, 540, 52, 52},
		{850, 690, 52, 52},
		{450, 120, 52, 52},
		{850, 500, 52, 52},
		{450, 500, 52, 52},
		{650, 200, 52, 52},
	};
	SDL_Rect result = pos[posIndex];
	posIndex++;
	if(posIndex == sizeof(pos) / sizeof(SDL_Rect)) {
		posIndex = 0;
	}
	return result;
}

void updateLinear(Answer* answer) {
	answer->posX += answer->speedX;
	answer->posY += answer->speedY;
}

void updateGravityDown(Answer* answer) {
	answer->speedY += ANSWER_GRAVITY;
	updateLinear(answer);
}

void updateGravityRight(Answer* answer) {
	answer->speedX += ANSWER_GRAVITY;
	updateLinear(answer);
}

void updateGravityLeft(Answer* answer) {
	answer->speedX -= ANSWER_GRAVITY;
	updateLinear(answer);
}

void updateRandomised(Answer* answer) {
	answer->speedX = rand() / (float)RAND_MAX * 3.0;
}

void answerChoosePattern(Answer* answer) {
	float r = rand() / (float)RAND_MAX;
	if(r < 0.25) {
		answer->updateFunc = updateLinear;
	} else if(r < 0.5) {
		answer->updateFunc = updateGravityDown;
	} else if(r < 0.75) {
		answer->updateFunc = updateGravityLeft;
	} else {
		answer->updateFunc = updateGravityRight;
	}
}
