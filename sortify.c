#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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
	if (argc > 1){
		srand(atoi(argv[1]));
	}
	else{
		srand(time(0));
	}

	char command;
	int run = 0, gameLevel = 1, gameScore = 0, gamePlays = 0, correct, randomNumbers[4], userNumbers[4];

	puts(MSG_WELCOME);
	print_menu();

	do{ command = getchar();

	switch (command)
	{
	case 'p':

		for (int i = 0; i < 4; i++){
			if (gameLevel == 1){
				randomNumbers[i] = rand_number(0, 10);
			}
			else if (gameLevel == 2){
				randomNumbers[i] = rand_number(0, 30);
			}
			else if (gameLevel == 3){
				randomNumbers[i] = rand_number(-50, 30);
			}
			else if (gameLevel == 4){
				randomNumbers[i] = rand_number(-100, 0);
			}
			else if (gameLevel == 5){
				randomNumbers[i] = rand_number(-200, -100);
			}
		}
		puts(MSG_SORT);
		printf("%d, %d, %d, %d\n", randomNumbers[0], randomNumbers[1], randomNumbers[2], randomNumbers[3]);
		scanf("%d %d %d %d", &userNumbers[0], &userNumbers[1], &userNumbers[2], &userNumbers[3]);
		gamePlays++;
		int unsorted = 1;
		while (unsorted){
			unsorted = 0;
			for (int i =0; i < 3; i++){
				if (randomNumbers[i] > randomNumbers[i + 1]){
					int aux = randomNumbers[i];
					randomNumbers[i] = randomNumbers[i + 1];
					randomNumbers[i + 1] = aux;
					unsorted = 1;
				}
			}
		}
		for (int i = 0; i < 4; i++){
			if (userNumbers[i] != randomNumbers[i]){
				puts(MSG_WRONG);
				correct = 0;
				break;
			}
			else{
				correct =1;
			}
		}
		if (correct){
			puts(MSG_WELL);
			gameScore += 5;
		}
		gameScore == 10 ? gameLevel = 2 : gameScore == 20 ? gameLevel = 3 : gameScore == 30 ? gameLevel = 4 : gameScore == 40 ? gameLevel = 5 : gameScore == 50 ? gameLevel = 6 : 0;

		if (gameLevel == 6){
			puts(MSG_WIN);
			print_status(gameLevel, gameScore, gamePlays);
			puts(MSG_OVER);
		}
		else if (gamePlays >= 30){
			puts(MSG_MAX);
			print_status(gameLevel, gameScore, gamePlays);
			puts(MSG_OVER);
		}
		break;

	case 'q':
		run = 1;
		print_status(gameLevel, gameScore, gamePlays);
		puts(MSG_BYE);
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
} while (run == 0);
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