#include "functions.h"
//intialies the players board
void init_board(char board[][10], int num_rows, int num_cols)
{
	int row_index = 0, col_index = 0;

	for (; row_index < num_rows; ++row_index) // traversing the rows
	{
		for (col_index = 0; col_index < num_cols; ++col_index) // traversing the cols
		{
			board[row_index][col_index] = '~';
		}
	}
}
// prints the players board
void print_board(char board[][10], int num_rows, int num_cols)
{
	int row_index = 0, col_index = 0;

	printf("%3d%2d%2d%2d%2d%2d%2d%2d%2d%2d\n", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);

	for (; row_index < num_rows; ++row_index) // traversing the rows
	{
		printf("%-2d", row_index);
		for (col_index = 0; col_index < num_cols; ++col_index) // traversing the cols
		{
			printf("%-2c", board[row_index][col_index]);
		}

		putchar('\n');
	}
}
// generates a random dierction of 0 or 2
int generate_dir(void)
{
	return rand() % 2;
}
//generates a random start point in the 2d array
void generate_start_pt(int* row_ptr, int* col_ptr, int length, int dir)
{
	if (dir == 0) // horizontal
	{
		*row_ptr = rand() % 10;
		*col_ptr = rand() % (10 - length + 1);
	}
	else // vertical
	{
		*row_ptr = rand() % (10 - length + 1);
		*col_ptr = rand() % 10;
	}
}
//updates the players stats
void update_stats(Stats* player_stats_ptr, int status)
{
	if (status == 0) // miss
	{
		(*player_stats_ptr).num_misses++;
	}
	else if (status == 1) // hit
	{
		(*player_stats_ptr).num_hits++;
	}

	player_stats_ptr->num_shots++;
}
//rules of the game
void welcome_screen(void)
{
	printf("Rules of the game\n");
	printf("Player1 is you and Player2 is the computer\n");
	printf("Player 1 gets to manually or automatically place the ships\n");
	printf("There are 5 different ships with different sizes: Carrier(c) with length of 5\n");
	printf("Battelship(b) with length of 4\n");
	printf("Cruizer(r) with length of 3\n");
	printf("Submarine(s) with length of 3\n");
	printf("destroyer(d) with length of 2\n");
	printf("The process of the game is to guess where enemy ships are and shoot it\n");
	printf("Whoever sinks the all the others ships wins\n");
}
//promts for a user input to place ships manually of automatically
int promt_input(void)
{
	int option = 0;
	printf("Player 1 do you want to input the ships manually or automatically (1 or 2)\n");
	scanf("%d", &option);
	return option;
}
// see who starts the game first, returns 0 or 1
int select_who_starts_first(void)
{
	int a = rand() % 2;
	return a;
}
//manually puts the ships on the board wither vertically downwards or horizantly to the right
void manually_place_ships_on_board(char board[][10], int num_rows, int num_cols, Ship_type ship[])
{
	print_board(board, 10, 10);

	int start_row = 0, start_col = 0, choice = 0, choice2 = 0;

	for (int i = 0; i < 5; i++)
	{
		/*printf("Where would you like to put the %s in the playground\n", ship[i].name);
		printf("row: ");
		scanf("%d", &start_row);
		printf("column: ");
		scanf("%d", &start_col);*/
		do
		{
			printf("Where would you like to put the %s in the playground\n", ship[i].name);
			printf("row: ");
			scanf("%d", &start_row);
			printf("column: ");
			scanf("%d", &start_col);

			printf("would you like to place the ship horzontially to the right or vertical downwards (0 or 1) \n");
			scanf("%d", &choice);
			choice2 = validate_choice(board, 10, 10, start_row, start_col, choice, ship[i].length);
		} while (choice2 != 1);

		for (int j = 0; j < ship[i].length; j++) {
			if (choice == 0)
				board[start_row][start_col + j] = ship[i].shape;
			if (choice == 1)
				board[start_row + j][start_col] = ship[i].shape;
			system("cls");
			print_board(board, 10, 10);
		}
		//print_board(board, 10, 10);
	}
	
}
// randomly places the ships on the board
void randomly_place_ships_onboard(char board[][10], int num_rows, int num_cols, Ship_type ship[])
{
	int ship_placed = 0, hor_or_vert = 0, rows = 0, cols = 0, choice3 = 0;
	while (ship_placed < 5)
	{
		do {
			hor_or_vert = generate_dir();
			generate_start_pt(&rows, &cols, ship[ship_placed].length, hor_or_vert);
			choice3 = validate_choice(board,10,10, num_rows, num_cols,hor_or_vert ,ship[ship_placed].length);
		} while (choice3 == 1);
		for (int j = 0; j < ship[ship_placed].length; j++) {
			if (hor_or_vert == 0)
				board[rows][cols + j] = ship[ship_placed].shape;
			if (hor_or_vert == 1)
				board[rows + j][cols] = ship[ship_placed].shape;
		}
		++ship_placed;
	}
	//print_board(board, 10, 10);
}
//checks if the arrays chosen are empty to place ships
int validate_choice(char board[][10], int num_row,int num_col,int start_row,int start_col,int choice, int length)
{
	{
		for (int i = 0; i < length; i++) {
			if (choice == 0)
				if (board[start_row][start_col + i] != '~')
					return 0;
			if (choice == 1)
				if (board[start_row + i][start_col] != '~')
					return 0;
		}
		return 1;
	}
}
// checks if shot is within range of board
int validate_shot(int row, int col)
{
	if (row <= 9 && row >= 0) {
		if (col <= 9 && col >= 0)
			return 1;
	}
	return 0;
}
//allows player to choose a target location to shoot
void player_attack(char board[][10], int num_row, int num_col, int ships_down[], Stats status, FILE* outfile)
{
	int row_fire = 0, col_fire = 0, confirm = 0;
	do
	{
		printf("Where do you want to shoot ?\n");
		printf("row: \n");
		scanf("%d", &row_fire);
		printf("col:\n");
		scanf("%d", &col_fire);
		confirm = validate_shot(row_fire, col_fire);
	} while (confirm = 0);

	if (board[row_fire][col_fire] != '~')
	{
		printf("It's a hit!!!\n");
		fprintf(outfile,"player 1's %d,%d is a hit\n", row_fire, col_fire);
		if (board[row_fire][col_fire] == 'c')
		{
			ships_down[0]--;
			if (ships_down[0] == 0)
			{
				printf("Player 1 has sunk the carrier\n");
				fprintf(outfile, "Player 1 has sunk the carrier\n");

			}
		}
		else if (board[row_fire][col_fire] == 'b')
		{
			ships_down[1]--;
			if (ships_down[1] == 0)
			{
				printf("Player 1 has sunk the battleship\n");
				fprintf(outfile, "Player 1 has sunk the battleship\n");

			}
		}
		else if (board[row_fire][col_fire] == 'r')
		{
			ships_down[2]--;
			if (ships_down[2] == 0)
			{
				printf("Player 1 has sunk the cruizer\n");
				fprintf(outfile, "Player 1 has sunk the cruizer\n");

			}
		}
		else if (board[row_fire][col_fire] == 's')
		{
			ships_down[3]--;
			if (ships_down[3] == 0)
			{
				printf("Player 1 has sunk the submarine\n");
				fprintf(outfile, "Player 1 has sunk the submarine\n");

			}
		}
		else if (board[row_fire][col_fire] == 'd')
		{
			ships_down[4]--;
			if (ships_down[4] == 0)
			{
				printf("Player 1 has sunk the destroyer\n");
				fprintf(outfile, "Player 1 has sunk the destroyer\n");

			}
		}
		status.num_hits++;
		board[row_fire][col_fire] = 'H'; //hit
	}
	else if (board[row_fire][col_fire] == '~')
	{
		printf("It's  a MISS\n");
		fprintf(outfile, "player 1's %d,%d is a miss\n", row_fire, col_fire);
		status.num_misses++;
		board[row_fire][col_fire] = 'm'; //missed 

	}
}
// automatically shoots a target location at player 1 board
void computer_attack(char board[][10], int num_row, int num_col, int ships_down[], Stats status, FILE* outfile,int shots_taken[][10])
{
	int row_fire = 0, col_fire = 0, confirm = 0;
	do
	{
		do {
			row_fire = rand() % num_row;
			col_fire = rand() % num_col;
		} while (shots_taken[row_fire][col_fire] != 0);
		shots_taken[row_fire][col_fire]++;

	} while (board[row_fire][col_fire]=='H' || board[row_fire][col_fire]=='m');

	if (board[row_fire][col_fire] != '~')
	{
		printf("computer got a  hit!!!\n");
		fprintf(outfile, "computer's %d,%d is a hit\n", row_fire, col_fire);
		if (board[row_fire][col_fire] == 'c')
		{
			ships_down[0]--;
			if (ships_down[0] == 0)
			{
				printf("computer has sunk the carrier\n");
				fprintf(outfile, "computer has sunk the carrier\n");

			}
		}
		else if (board[row_fire][col_fire] == 'b')
		{
			ships_down[1]--;
			if (ships_down[1] == 0)
			{
				printf("computer has sunk the battleship\n");
				fprintf(outfile, "computer has sunk the battleship\n");

			}
		}
		else if (board[row_fire][col_fire] == 'r')
		{
			ships_down[2]--;
			if (ships_down[2] == 0)
			{
				printf("computer has sunk the cruizer\n");
				fprintf(outfile, "computer has sunk the cruizer\n");

			}
		}
		else if (board[row_fire][col_fire] == 's')
		{
			ships_down[3]--;
			if (ships_down[3] == 0)
			{
				printf("computer has sunk the submarine\n");
				fprintf(outfile, "computer has sunk the submarine\n");

			}
		}
		else if (board[row_fire][col_fire] == 'd')
		{
			ships_down[4]--;
			if (ships_down[4] == 0)
			{
				printf("computer has sunk the destroyer\n");
				fprintf(outfile, "computer has sunk the destroyer\n");

			}
		}
		status.num_hits++;
		board[row_fire][col_fire] = 'H'; //hit
	}
	else if (board[row_fire][col_fire] == '~')
	{
		printf("Computer got a MISS\n");
		fprintf(outfile, "computer's %d,%d is a miss\n", row_fire, col_fire);
		status.num_misses++;
		board[row_fire][col_fire] = 'm'; //missed 

	}
}
// checks if all the ships are sunk
int check_if_sunk_ship(int ships_down[])
{
	for (int i = 0; i < 5; i++)
	{
		if (ships_down[i] == 0)
		{
			return 0;
		}

	}
	return 1;
}
//outputs the stats to the log file 
void output_stats(Stats p1_stats, Stats p2_stats, FILE* outfile)
{
	fprintf(outfile, "player 1 number of hits: %d\n", p1_stats.num_hits);
	fprintf(outfile, "player 1 number of shots: %d\n", p1_stats.num_shots);
	fprintf(outfile, "player 1 number of misses: %d\n", p1_stats.num_misses);
	fprintf(outfile, "player 1 number of misses: %lf\n", p1_stats.num_hits/p1_stats.num_misses);
	fprintf(outfile, "player 2 number of hits: %d\n", p2_stats.num_hits);
	fprintf(outfile, "player 2 number of shots: %d\n", p2_stats.num_shots);
	fprintf(outfile, "player 2 number of misses: %d\n", p2_stats.num_misses);
	fprintf(outfile, "player 2 number of misses: %lf\n", p2_stats.num_hits / p1_stats.num_misses);
}