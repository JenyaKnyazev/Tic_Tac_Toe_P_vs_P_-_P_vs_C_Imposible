#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
void print_board(char board[3][3]) {
	printf("\t%c|%c|%c\n", board[0][0], board[0][1], board[0][2]);
	puts("\t-----");
	printf("\t%c|%c|%c\n", board[1][0], board[1][1], board[1][2]);
	puts("\t-----");
	printf("\t%c|%c|%c\n", board[2][0], board[2][1], board[2][2]);
}
int check_win(char board[3][3]) {
	int i;
	for (i = 0; i < 3; i++) {
		if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
			return 1;
		if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[2][i] == board[1][i])
			return 1;
	}
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
		return 1;
	if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
		return 1;
	return 0;
}
void clean_board(char board[3][3]) {
	int i, r;
	for (i = 0; i < 3; i++)
		for (r = 0; r < 3; r++)
			board[i][r] = ' ';
}
char choose() {
	int n;
	puts("Choose X or O ,1 = X , Other = O");
	scanf("%d", &n);
	return (n == 1) ? 'X' : 'O';
}
void player_move(char board[3][3], char player) {
	int row, col;
	printf("Player %c move: ", player);
	scanf("%d %d", &row, &col);
	while (row > 3 || row < 1 || col>3 || col < 1 || board[row - 1][col - 1] != ' ') {
		printf("Invalid move Player %c move: ", player);
		scanf("%d %d", &row, &col);
	}
	board[row - 1][col - 1] = player;
}
void player_vs_player() {
	char player1;
	char player2;
	char board[3][3];
	int count_moves;
	int again;
	do {
		clean_board(board);
		puts("Player 1");
		player1 = choose();
		player2 = (player1 == 'X') ? 'O' : 'X';
		count_moves = 0;
		print_board(board);
		while (1) {
			printf("Player 1\n");
			player_move(board, player1);
			print_board(board);
			if (check_win(board)) {
				printf("Player 1 %c WIN\n", player1);
				break;
			}
			count_moves++;
			if (count_moves == 9) {
				puts("Tie Draw");
				break;
			}
			printf("Player 2\n");
			player_move(board, player2);
			print_board(board);
			if (check_win(board)) {
				printf("Player 2 %c WIN\n", player2);
				break;
			}
			count_moves++;
		}
		printf("Again = 1, Exit = Other: ");
		scanf("%d", &again);
	} while (again == 1);
}
void computer_move_easy(char board[3][3], char computer) {
	int row, col;
	do {
		row = rand() % 3;
	} while (board[row][0] != ' ' && board[row][1] != ' ' && board[row][2] != ' ');
	do {
		col = rand() % 3;
	} while (board[row][col] != ' ');
	board[row][col] = computer;
}
void delay(int milliseconds) {
	clock_t start = clock();
	while (clock() < start + milliseconds);
}
void delay_dots(int milliseconds) {
	while (milliseconds > 0) {
		delay(100);
		printf(". ");
		milliseconds -= 100;
	}
}
void player_vs_computer_easy() {
	char player;
	char computer;
	char board[3][3];
	int count_moves;
	int again;
	do {
		clean_board(board);
		puts("Player");
		player = choose();
		computer = (player == 'X') ? 'O' : 'X';
		count_moves = 0;
		print_board(board);
		while (1) {
			printf("Player\n");
			player_move(board, player);
			print_board(board);
			if (check_win(board)) {
				printf("Player %c WIN\n", player);
				break;
			}
			count_moves++;
			if (count_moves == 9) {
				puts("Tie Draw");
				break;
			}
			printf("Computer move: ");
			delay_dots(2000);
			putchar('\n');
			computer_move_easy(board, computer);
			print_board(board);
			if (check_win(board)) {
				printf("Computer %c WIN\n", computer);
				break;
			}
			count_moves++;
		}
		printf("Again = 1, Exit = Other: ");
		scanf("%d", &again);
	} while (again == 1);
}
int connect_3_computer(char board[3][3], char computer) {
	int i, r, j, count;
	char player;
	for (i = 0; i < 3; i++)
		for (r = 0; r < 3; r++)
			if (board[i][r] == ' ') {
				count = 0;
				for (j = 0; j < 3; j++)
					if (board[i][j] == computer)
						count++;
				if (count == 2) {
					board[i][r] = computer;
					return 1;
				}
				count = 0;
				for (j = 0; j < 3; j++)
					if (board[j][r] == computer)
						count++;
				if (count == 2) {
					board[i][r] = computer;
					return 1;
				}
			}
	for (i = 0; i < 3; i++)
		if (board[i][i] == ' ')
			if ((board[0][0] == computer) + (board[1][1] == computer) + (board[2][2] == computer) == 2) {
				board[i][i] = computer;
				return 1;
			}
	for (i = 0, r = 2; i < 3; i++, r--)
		if (board[i][r] == ' ')
			if ((board[0][2] == computer) + (board[1][1] == computer) + (board[2][0] == computer) == 2) {
				board[i][r] = computer;
				return 1;
			}
	player = (computer == 'X') ? 'O' : 'X';
	for (i = 0; i < 3; i++)
		for (r = 0; r < 3; r++)
			if (board[i][r] == ' ') {
				count = 0;
				for (j = 0; j < 3; j++)
					if (board[i][j] == player)
						count++;
				if (count == 2) {
					board[i][r] = computer;
					return 1;
				}
				count = 0;
				for (j = 0; j < 3; j++)
					if (board[j][r] == player)
						count++;
				if (count == 2) {
					board[i][r] = computer;
					return 1;
				}
			}
	for (i = 0; i < 3; i++)
		if (board[i][i] == ' ')
			if ((board[0][0] == player) + (board[1][1] == player) + (board[2][2] == player) == 2) {
				board[i][i] = computer;
				return 1;
			}
	for (i = 0, r = 2; i < 3; i++, r--)
		if (board[i][r] == ' ')
			if ((board[0][2] == player) + (board[1][1] == player) + (board[2][0] == player) == 2) {
				board[i][r] = computer;
				return 1;
			}
	return 0;
}
void computer_move_medium(char board[3][3], char computer) {
	if (connect_3_computer(board, computer) == 0)
		computer_move_easy(board, computer);
}
void player_vs_computer_medium() {
	char player;
	char computer;
	char board[3][3];
	int count_moves;
	int again;
	do {
		clean_board(board);
		puts("Player");
		player = choose();
		computer = (player == 'X') ? 'O' : 'X';
		count_moves = 0;
		print_board(board);
		while (1) {
			printf("Player\n");
			player_move(board, player);
			print_board(board);
			if (check_win(board)) {
				printf("Player %c WIN\n", player);
				break;
			}
			count_moves++;
			if (count_moves == 9) {
				puts("Tie Draw");
				break;
			}
			printf("Computer move: ");
			delay_dots(2000);
			putchar('\n');
			computer_move_medium(board, computer);
			print_board(board);
			if (check_win(board)) {
				printf("Computer %c WIN\n", computer);
				break;
			}
			count_moves++;
		}
		printf("Again = 1, Exit = Other: ");
		scanf("%d", &again);
	} while (again == 1);
}
void computer_move_imposible(char board[3][3], char computer, int* first_move, int* second_move) {
	int i, r;
	int rows[] = { 0,1,1,2 };
	int cols[] = { 1,0,2,1 };
	int rows2[] = { 0,0,2,2 };
	int cols2[] = { 0,2,0,2 };
	char player = (computer == 'X') ? 'O' : 'X';
	if (*first_move) {
		if (board[1][1] == ' ') {
			board[1][1] = computer;
		}
		else {
			i = rand() % 4;
			board[rows2[i]][cols2[i]] = computer;
		}
		*first_move = 0;
	}
	else if (*second_move) {
		if (connect_3_computer(board, computer) == 0) {
			if (board[0][0] == player && board[2][2] == player || board[0][2] == player && board[2][0] == player) {
				i = rand() % 4;
				board[rows[i]][cols[i]] = computer;
			}
			else {
				do {
					i = rand() % 4;
				} while (board[rows2[i]][cols2[i]] != ' ');
				board[rows2[i]][cols2[i]] = computer;
			}
		}
		*second_move = 0;
	}
	else
		computer_move_medium(board, computer);
}
void player_vs_computer_imposible() {
	char player;
	char computer;
	char board[3][3];
	int count_moves;
	int again;
	int first_move;
	int second_move;
	do {
		clean_board(board);
		puts("Player");
		player = choose();
		computer = (player == 'X') ? 'O' : 'X';
		count_moves = 0;
		first_move = 1;
		second_move = 1;
		print_board(board);
		while (1) {
			printf("Player\n");
			player_move(board, player);
			print_board(board);
			if (check_win(board)) {
				printf("Player %c WIN\n", player);
				break;
			}
			count_moves++;
			if (count_moves == 9) {
				puts("Tie Draw");
				break;
			}
			printf("Computer move: ");
			delay_dots(2000);
			putchar('\n');
			computer_move_imposible(board, computer, &first_move, &second_move);
			print_board(board);
			if (check_win(board)) {
				printf("Computer %c WIN\n", computer);
				break;
			}
			count_moves++;
		}
		printf("Again = 1, Exit = Other: ");
		scanf("%d", &again);
	} while (again == 1);
}
void run() {
	srand(time(NULL));
	int ch, ch2;
	do {
		puts("Tic Tac Toe");
		puts("To play you need to enter row and col from 1-3 like \"1 1\"");
		puts("Enter 1 = Player vs Player \nEnter 2 = Player vs Computer\nEnter Other = Exit");
		scanf("%d", &ch);
		switch (ch) {
		case 1:
			player_vs_player();
			break;
		case 2:
			do {
				puts("Enter 1 = Easy");
				puts("Enter 2 = Medium");
				puts("Enter 3 = IMPOSIBLE");
				puts("Enter Other = Back");
				scanf("%d", &ch2);
				switch (ch2) {
				case 1:
					player_vs_computer_easy();
					break;
				case 2:
					player_vs_computer_medium();
					break;
				case 3:
					player_vs_computer_imposible();
					break;
				}
			} while (ch2 >= 1 && ch2 <= 3);
			break;
		}
	} while (ch == 1 || ch == 2);
	puts("Good Bye");
}
void main() {
	run();
	system("pause");
}
