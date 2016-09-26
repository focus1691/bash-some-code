#ifndef _QUESTIONS_H_INCLUDED
#define _QUESTIONS_H_INCLUDED

#define LEVELS 4
#define QUESTIONS_FOR_LEVEL 5

typedef struct {
	char* text;
	int answer;
} Question;

Question* getQuestion(int level, int round);


#endif
