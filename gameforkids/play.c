#include <stdio.h>
#include <stdbool.h>

#include "display.h"
#include "battle.h"
#include "questions.h"

#define ROUNDS_PER_LEVEL 5
#define ANSWERS 7
typedef enum {START, BATTLE, END} GameState;

int main(int argc, char** argv)
{
	GameState gameState = START;
	bool gameIsOn = true;
	int currentLevel = 0;
	int currentRound = 0;
	Display display;
	(void)argc;
	(void)argv;

	while(gameIsOn) {
		switch(gameState) {
			case START:
				graphicsInit();
				displayInit(&display, "Game");
				gameState = BATTLE;
				SDL_SetWindowSize(display.window, WINDOW_WIDTH, WINDOW_HEIGHT);
				break;
			case BATTLE:
				if(battleRun(&display, getQuestion(currentLevel, currentRound), ANSWERS, currentLevel, currentRound)) {
					currentRound++;
				}
				if(currentRound == ROUNDS_PER_LEVEL) {
					currentRound = 0;
					currentLevel++;
				}
				if(currentLevel == LEVELS) {
					gameState = END;
				}
				break;
			case END:
				displayFree(&display);
				gameIsOn = false;
				break;
		}
	}
	return 0;
}
