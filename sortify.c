#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MSG_WELCOME "WELCOME TO SORTIFY!"
#define MSG_SORT "Sort the following numbers:"
#define MSG_SORT2 "Please sort the numbers"
#define MSG_WELL "Well done!"
#define MSG_WIN "Congratulations, you win!"
#define MSG_OVER "Game Over."
#define MSG_WRONG "Wrong answer."
#define MSG_MAX "You have reached the maximum number of moves."
#define MSG_BYE "Bye."
#define MSG_UNKNOWN "Unknown option."
/* Use puts() to print constant strings */

int rand_number(const int, const int);
void print_status(const int, const int, const int);
void print_menu(void);


int main(int argc, char **argv)
{
	char command;
	int gameOver = 0, gameLevel = 1, gameScore = 0, gamePlays = 0, random_Numbers[4], userNumbers[4];


	puts(MSG_WELCOME);
	print_menu();

	do{ command = getchar();

	switch (command)
	{
	case 'p':
		for (int i = 0; i < 4; i++){
			if (gameLevel == 1){
				random_Numbers[i] = rand_number(0, 10);
			}
			else if (gameLevel == 2){
				random_Numbers[i] = rand_number(0, 30);
			}
			else if (gameLevel == 3){
				random_Numbers[i] = rand_number(-50, 30);
			}
			else if (gameLevel == 4){
				random_Numbers[i] = rand_number(-100, 0);
			}
			else if (gameLevel == 5){
				random_Numbers[i] = rand_number(-200, -100);
			}
		}
		puts(MSG_SORT);
		printf("%d, %d, %d, %d\n", random_Numbers[0], random_Numbers[1], random_Numbers[2], random_Numbers[3]);
		scanf("%d %d %d %d", userNumbers[0], userNumbers[1], userNumbers[2], userNumbers[3]);
		break;

	case 'q':
		gameOver = 1;
		break;

	case 'm':
		print_menu();
		break;

	case 's':
		print_status(gameLevel, gameScore, gamePlays);
		break;
	
	default:
		break;
	}
} while (gameOver == 0);
	return 0;
}

/* generate a random integer between min and max */
int rand_number(const int min, const int max)
{
	if (max < min)
	{
		puts("Max must be larger than Min");
		exit(0);
	}
	int n = abs(max - min) + 1;
	return (rand() % n) + min;
}

/* print the game status */
void print_status(const int level, const int score, const int plays)
{
	puts("+-----------------------------+");
	printf("| level:  %02d                  |\n", level);
	printf("| points: %02d                  |\n", score);
	printf("| plays:  %02d                  |\n", plays);
	puts("+-----------------------------+");
}

/* print the option menu */
void print_menu(void)
{
	puts("+-----------------------------+");
	puts("| SORTIFY                     |");
	puts("| p - next chalenge           |");
	puts("| q - quit                    |");
	puts("| m - print this information  |");
	puts("| s - show your status        |");
	puts("+-----------------------------+");
}