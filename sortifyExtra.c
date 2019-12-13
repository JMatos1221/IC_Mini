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
int timedScore();
clock_t startTime, totalTime;

int main(int argc, char **argv)
{
	if (argc > 1){
		srand(atoi(argv[1])); //Receber seed
	}
	else{
		srand(time(0)); //Gerar seed baseada no tempo
	}

	char command;
	int run = 1, gameLevel = 1, gameScore = 0, gamePlays = 0, correct = 0, present = 0, randomNumbers[4], userNumbers[4];

	puts(MSG_WELCOME);
	print_menu();

	do{ scanf(" %c", &command); //Scan do comando (p, q, s, m)

	switch (command)
	{
	case 'p':

		startTime = clock();

		for (int i = 0; i < 4; i++){ //Gera o intervalo de numeros consoante o nivel
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
		printf("%d, %d, %d, %d\n", randomNumbers[0], randomNumbers[1], randomNumbers[2], randomNumbers[3]); //Imprime o intervalo de numeros gerado
		do{
		scanf("%d %d %d %d", &userNumbers[0], &userNumbers[1], &userNumbers[2], &userNumbers[3]); //Recebe os numeros do utilizador
		int unsorted = 1;
		while (unsorted){ //Ordena os numeros, sendo que apenas sai do ciclo quando o `if` nao se verificar (unsorted continua a ser 0)
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
		for (int i = 0; i < 4; i++){ //Verifica se todos os numeros inseridos estao no array gerado consoante o nivel
			present = 0;
			for (int j = 0; j < 4; j++){
				if (userNumbers[i] == randomNumbers[j]){
					present = 1;
    			}
    		}
			if (present == 0){break;} //Para de verificar se nao tiver presente
		}

		if (present == 0){
			puts(MSG_SORT2);
		}

		} while (present == 0); //Loop ate todos os numeros estarem presentes

		gamePlays++;

		for (int i = 0; i < 4; i++){ //Verifica se os numeros estao corretamente ordenados, imprime MSG_WRONG caso nao estejam
					if (userNumbers[i] != randomNumbers[i]){
						puts(MSG_WRONG);
						correct = 0;
						break;
					}
					else{
						correct =1;
					}
				}
            
		if (correct){ //Imprime MSG_WELL se tudo estiver corretamente ordenado
			puts(MSG_WELL);
			gameScore += timedScore();
		}
		gameScore >= 50 ? gameLevel = 6 : gameScore >= 40 ? gameLevel = 5 : gameScore >= 30 ? gameLevel = 4 : gameScore >= 20 ? gameLevel = 3 : gameScore >= 10 ? gameLevel = 2 : 0; //Verifica os pontos do jogador e se suficientes sobe o nivel

		if (gameLevel == 6){ //Caso o jogador chegue ao nivel 6 (Fim), imprime MSG_WIN, status e MSG_OVER, depois termina o jogo
			puts(MSG_WIN);
			print_status(gameLevel, gameScore, gamePlays);
			puts(MSG_OVER);
			run = 0;
		}
		else if (gamePlays >= 30){ //Caso o jogador chegue as 30 jogadas sem chegar ao nivel 6, imprimie MSG_MAX, status, MSG_OVER e termina o jogo
			puts(MSG_MAX);
			print_status(gameLevel, gameScore, gamePlays);
			puts(MSG_OVER);
			run = 0;
		}
		break;

	case 'q': //Comando para sair do jogo, imprime status e MSG_BYE
		run = 0;
		print_status(gameLevel, gameScore, gamePlays);
		puts(MSG_BYE);
		break;

	case 'm': //Comando para imprimir o menu
		print_menu();
		break;

	case 's': //Comando para imprimir o status
		print_status(gameLevel, gameScore, gamePlays);
		break;
	
	default: //Imprime MSG_UNKNOWN quando o comando nao existe
		puts(MSG_UNKNOWN);
		break;
	}
} while (run == 1); //Loop que mantem o jogo a correr
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

int timedScore(){
	totalTime = clock() - startTime;
	totalTime = ((int) totalTime) / CLOCKS_PER_SEC;
	if (totalTime <= 5){
		return 10;
	}
	else if (totalTime > 15){
		return 1;
	}
	else{
		totalTime = 15 - totalTime;
		return totalTime;
	}
}