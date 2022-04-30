#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include <math.h>
#include <stdlib.h> //rand() , scrand()
#include <time.h> //srand  --> time()

typedef struct stats
{
	int num_hits;
	int num_misses;
	int num_shots;
	double hits_misses_ratio;
} Stats;

typedef struct ship_type {
	char* name;
	char shape;
	int length;
}Ship_type;

void welcome_screen(void);
void init_board(char board[][10], int num_rows, int num_cols);
void print_board(char board[][10], int num_rows, int num_cols);

int select_who_starts_first(void);
int generate_dir(void);
void generate_start_pt(int* row_ptr, int* col_ptr, int length, int dir);

void update_stats(Stats* player_stats_ptr, int status);

int promt_input(void);

void manually_place_ships_on_board(char board[][10], int num_rows, int num_cols, Ship_type ship[]);
void randomly_place_ships_onboard(char board[][10], int num_rows, int num_cols, Ship_type ship[]);
int validate_choice(char board[][10], int num_row, int num_col, int start_row, int start_col, int choice, int length);
int validate_shot(int row, int col);
void player_attack(char board[][10], int num_row, int num_col, int ships_down[], Stats status, FILE* outfile);
void computer_attack(char board[][10], int num_row, int num_col, int ships_down[], Stats status, FILE* outfile, int shots_taken[][10]);
int check_if_sunk_ship(int ships_down[]);
void output_stats(Stats p1_stats, Stats p2_stats, FILE* outfile);

#endif