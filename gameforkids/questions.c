#include <stdlib.h>
#include "questions.h"

static Question questions[LEVELS][QUESTIONS_FOR_LEVEL] = {
	{
		{"x = 5 + 3;", 8},
		{"x = 1 + 5;", 6},
		{"x = -7 + 3;", -4},
		{"x = -9 + 17;", 8},
		{"x = 25 - 9;", 16},
	},
	{
		{"x = -4 * -2;", 8},
		{"x = -1; x *= 5;", -5},
		{"x = 6; x /= 2;", 3},
		{"x = 15; x /= 3;", 5},
		{"x = -4; x *= 4;", -16},
	},
	{
		{"int x=5; "
	 	 "(x == 5) ? x = 10 : x = 20; "
		 "x ?", 10},

		{"int x= -5; "
	 	 "(x > 0) ? x += 5: x -= 5; "
		 "y = ?", -10},

		{"int x = 10; int y = 9; "
		 "(x < y) ? x = y: y = x; "
		 "x = ?", 10},

		{"int x = 8; int y = 8; "
		 "(x != y) ? x += x: x -= x; "
	 	 "y = ?", 16},

		{"int x = 10; int y = 5; "
		 "(x > y) ? x = 2; y = 2; "
		 "x = ?", 2},
	},
	{
		{"int x=2; "
	 	 "for(i=0;i<2;i++) { "
		 "x*=2 }", 8},

		{"int x = 2;"
		 "for(i=0;i<5;i++) { "
		 "x=3; }", 3},

		{"for(i=3;i>0;i--) { "
		 "x+=1; }", 3},

		{"int x=5; "
		 "for(i=1;i<4;i++) { "
		 "x+=2; }", 11},

		{"int x=2; "
		 "for(i=0;i<5;i++) { "
		 "x *= x; }", 32},
	}
};

Question* getQuestion(int level, int round) {
	(void)round;
	return &questions[level][rand() % QUESTIONS_FOR_LEVEL];
}
