#ifndef _BATTLE_H_INCLUDED
#define _BATTLE_H_INCLUDED

#include <stdbool.h>

#include "display.h"
#include "questions.h"

#define ANSWER_COUNT_MAX 16
#define COMPUTER_INITIAL_HEALTH 2000
#define WRONG_ANSWER_CATCH_PENALTY 1000
#define WRONG_ANSWER_COLLISION_PENALTY 20
#define ANSWER_RANGE 5

bool battleRun(Display* display, const Question* question, int answerCount, int level, int round);

#endif
