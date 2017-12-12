/*
** EPITECH PROJECT, 2017
** Project bsq
** File description:
** Header file
*/

#ifndef MAIN_H_
#define MAIN_H_

typedef struct square_pos_s {
	int size;
	int x;
	int y;
} square_pos;

int get_nbr_size(int nb);
int get_line_nbr(char *filename);
int get_colon_nbr(char *filename, int max_y);
char **create_map(char **result, char *filename, int x, int y);
void print_map(char **map, square_pos square, int x);
void find_x(char **map, int *tab);
square_pos find_square(char **map, int y, int x, int max_y);
square_pos find_final(square_pos final, char **map, int *tab, int i);
void bsq(char **map, int max_x, int max_y);

#endif
