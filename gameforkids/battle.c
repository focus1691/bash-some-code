#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "display.h"
#include "battle.h"
#include "answers.h"
#include "computer.h"
#include "hero.h"

#define QUESTION_FONT_SIZE 50

bool battleRun(Display* display, const Question* question, int answerCount, int level, int round) {
	int i;
	SDL_Rect qRect = {0, 40, 0, 0};
	bool battle = true;
	bool result = false;
	Answer answers[ANSWER_COUNT_MAX];
	SDL_Event event;
	SDL_Color qColor = RED;
	Computer computer;
	SDL_Rect computerPos = {400, 600, 100, 100};
	Hero hero;
	SDL_Rect heroPos = {400, WINDOW_HEIGHT - 100, 100, 100};

	SDL_Texture* roundNoTexture;
	char roundNoStr[32];
	SDL_Rect roundNoRect = {WINDOW_WIDTH - 80, WINDOW_HEIGHT - 100, 40, 50};

	SDL_Texture* levelNoTexture;
	char levelNoStr[32];
	SDL_Rect levelNoRect = {WINDOW_WIDTH - 80, WINDOW_HEIGHT - 150, 40, 50};

	SDL_Texture* bg = loadTexture(display->renderer, "background1.jpg");
	SDL_Texture* qTexture = textTexture(display->renderer, question->text, MAIN_FONT, QUESTION_FONT_SIZE, qColor);

	sprintf(roundNoStr, "%d", round + 1);
	roundNoTexture = textTexture(display->renderer, roundNoStr, MAIN_FONT, QUESTION_FONT_SIZE, qColor);
	
	sprintf(levelNoStr, "%d", level + 1);
	levelNoTexture = textTexture(display->renderer, levelNoStr, MAIN_FONT, QUESTION_FONT_SIZE, qColor);

	SDL_QueryTexture(qTexture, NULL, NULL, &qRect.w, &qRect.h);

	srand(time(NULL));

	computerInit(&computer, COMPUTER_INITIAL_HEALTH, computerPos, display->renderer);
	heroInit(&hero, heroPos, display->renderer);

	answerInit(&answers[0], question->answer, true, getPos(), display->renderer);
	for(i = 1; i < answerCount; i++) {
		answerInit(&answers[i], question->answer + rand() % ANSWER_RANGE - 2 * ANSWER_RANGE, false, getPos(), display->renderer);
	}

	while(battle) {
		SDL_PollEvent(&event);
		switch(event.type) {
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case SDLK_LEFT:
						heroLeft(&hero);
						break;
					case SDLK_RIGHT:
						heroRight(&hero);
						break;
					case SDLK_SPACE:
						heroJump(&hero);
						break;
				}
				break;

			case SDL_KEYUP:
				switch(event.key.keysym.sym) {
					case SDLK_LEFT:
						heroStopLeft(&hero);
						break;
					case SDLK_RIGHT:
						heroStopRight(&hero);
						break;
				}
				break;
			case SDL_QUIT:
				exit(1);
		}
		SDL_RenderClear(display->renderer);
		SDL_RenderCopy(display->renderer, bg, NULL, NULL);
		SDL_RenderCopy(display->renderer, qTexture, NULL, &qRect);
		SDL_RenderCopy(display->renderer, roundNoTexture, NULL, &roundNoRect);
		SDL_RenderCopy(display->renderer, levelNoTexture, NULL, &levelNoRect);
		computerRender(&computer, display);
		heroUpdate(&hero);
		heroRender(&hero, display);
		for(i = 0; i < answerCount; i++) {
			if(answers[i].isAlive) {
				answerUpdate(&answers[i]);
				if(SDL_HasIntersection(&answers[i].pos, &hero.pos)) {
					answers[i].isAlive = false; 
					if(answers[i].isCorrect) {
						result = true;
						battle = false;
					} else {
						computer.health -= WRONG_ANSWER_CATCH_PENALTY;
					}
				}
				if(!answers[i].isCorrect && SDL_HasIntersection(&answers[i].pos, &computer.pos)) {
					computer.health -= WRONG_ANSWER_COLLISION_PENALTY;
				}
				answerRender(display, &answers[i]);
			}
		}
		if(computer.health <= 0) {
			break;
		}
		SDL_RenderPresent(display->renderer);
	}

	for(i = 0; i < answerCount; i++) {
		answerFree(&answers[i]);
	}
	computerFree(&computer);
	SDL_DestroyTexture(bg);
	SDL_DestroyTexture(qTexture);
	SDL_DestroyTexture(roundNoTexture);
	return result;
}
