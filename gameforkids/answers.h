#ifndef _ANSWERS_H_INCLUDED
#define _ANSWERS_H_INCLUDED

#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "display.h"

#define VIRUS_IMAGE "virus.png"
#define ANSWER_GRAVITY 0.2

typedef struct Answer Answer;

struct Answer{
	bool isCorrect;
	SDL_Rect pos;
	float speedX, speedY;
	float posX, posY;
	SDL_Texture* texture;
	void (*updateFunc)(Answer*);
	bool isAlive;
};

void answerInit(Answer* answer, int value, bool isCorrect, SDL_Rect pos, SDL_Renderer* renderer);
void answerFree(Answer* answer);
void answerUpdate(Answer* answer);
void answerRender(Display* display, Answer* answer);
SDL_Rect getPos(void);

#endif
