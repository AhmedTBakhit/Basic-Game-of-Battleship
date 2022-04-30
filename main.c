#include "functions.h"

int main(void)
{
	int option = 0, decision = 0, start_first = 0;

	while (option == 0)
	{
		
		welcome_screen();
		printf("ENTER 1 TO START THE GAME");
		scanf("%d", &option);


	} 
	system("cls");
	Stats p1_stats = { 0, 0, 0, 0.0 }, p2_stats = { 0, 0, 0, 0.0 };
	char p1_board[10][10] = { {'~', '~'} };
	char p2_board[10][10] = { {'~', '~'} };

	srand((unsigned int)time(NULL));

	init_board(p1_board, 10, 10);
	init_board(p2_board, 10, 10);
	//print_board(p1_board, 10, 10);
	//print_board(p2_board, 10, 10);

	Ship_type ship[5] = { {"carrier",'c',5},{"battleship",'b',4},{"cruiser",'r',3},{"submarine",'s',3},{"destroyer",'d',2}};
	int ships_down_p1[5] = { 5,4,3,3,2 }, ships_down_p2[5] = {5,4,3,3,2};
	int shots_taken[10][10] = { 0 };

	FILE* outfile = NULL;
	outfile = fopen("battleship.log", "w");

	decision = promt_input();

	if (decision == 1)
	{
		manually_place_ships_on_board(p1_board,10,10,ship);
		print_board(p1_board, 10, 10);
	}

	else if(decision ==2)
	{
	    randomly_place_ships_onboard(p1_board,10,10,ship);
		print_board(p1_board, 10, 10);
	}
	randomly_place_ships_onboard(p2_board, 10, 10, ship);
	printf("player 2 (computers) board has been generated\n");
	start_first = select_who_starts_first();

	if (start_first == 1)
	{
		//system("cls");
		printf("You start first\n");
		fprintf(outfile, "Player 1 started first\n");
		player_attack(p2_board, 10, 10, ships_down_p2, p1_stats, outfile);
	}
	else if (start_first == 0)
	{
		//system("cls");
		printf("computer starts first\n");
		fprintf(outfile, "The computer has started first\n");
		//computer_attack(p1_board, 10, 10, ships_down_p1, p2_stats, outfile, shots_taken);
	}

	do {
		computer_attack(p1_board, 10, 10, ships_down_p1, p2_stats, outfile, shots_taken);
		player_attack(p2_board, 10, 10, ships_down_p2, p1_stats, outfile);


	} while (check_if_sunk_ship(ships_down_p1) == 1 || check_if_sunk_ship(ships_down_p2) == 1);

	system("cls");

	if (check_if_sunk_ship(ships_down_p1) == 0)
	{
		printf("The computer has won\n");
		fprintf(outfile, "computer won\n");
	}

	if (check_if_sunk_ship(ships_down_p2) == 0)
	{
		printf("You have won\n");
		fprintf(outfile, "Player 1 won\n");
	}

	output_stats( p1_stats, p2_stats,  outfile);
	//print_board(p1_board, 10, 10);

	//update_stats(&p1_stats, 1);

	fclose(outfile);

	return 0;
}