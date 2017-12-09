/*
** EPITECH PROJECT, 2017
** Project bsq
** File description:
** Main file.
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "main.h"

int get_line_nbr(char *filename)
{
	int file = open(filename, O_RDONLY);
	char buffer[1];
	char *str;
	int i = 0;
	int res;

	while (read(file, buffer, 1) > 0 && buffer[0] != '\n')
		i = i + 1;
        str = malloc(i + 1);
	close(file);
	file = open(filename, O_RDONLY);
	read(file, str, i);
	res = my_getnbr(str);
	free(str);
	close(file);
	return (res);
}

int get_colon_nbr(char *filename)
{
	int file = open(filename, O_RDONLY);
	char buffer[1];
	int i = 0;

	while (read(file, buffer, 1) > 0 && buffer[0] != '\n');
	while (read(file, buffer, 1) > 0 && buffer[0] != '\n')
		i = i + 1;
	close(file);
	return (i);
}

char **create_map(char **result, char *filename, int x, int y)
{
	int file = open(filename, O_RDONLY);
	char buffer[1];
	int c = 0;

	while (read(file, buffer, 1) > 0 && buffer[0] != '\n');
	result = malloc(sizeof(char *) * x + 1);
	for (int i = 0; i < x; i = i + 1, c = 0) {
		result[i] = malloc(y + 1);
		for (; c < y; c = c + 1) {
			read(file, buffer, 1);
			result[i][c] = buffer[0];
		}
		read(file, buffer, 1);
	}
	return (result);
}

void print_map(char **map, square_pos square)
{
	for (int y = square.y; square.y + square.size > y; y = y + 1) {
		for (int x = square.x; square.x + square.size > x; x = x + 1) {
			map[y][x] = 'x';
		}
	}
	for (int i = 0; map[i] != NULL; i = i + 1, my_putchar('\n'))
		my_putstr(map[i]);
}

square_pos find_square(char **map, int y, int x, int max_y)
{
	int tmp_y = 0;
	int tmp_x = 0;
	int ltc = 0;
	int ctc = 0;
	square_pos taille = {-2, -1, -1};
	int end = 1;

        while (end) {
		if (map[y][x + 1] == '.') {
	        	ltc = ltc + 1;
			ctc += 1;
		} else {
			end = 0;
		}
	        while (ltc > tmp_y) {
			if (tmp_y + y + 1 >= max_y)
				end = 0;
			while (ctc > tmp_x) {
				if (map[y + tmp_y][x + tmp_x] != '.') {
					end = 0;
					ctc = ctc - 1;
				}
				tmp_x += 1;
			}
		        tmp_x = 0;
			tmp_y += 1;
		}
		if (taille.size < ctc) {
			taille.size = ctc;
			taille.x = x;
			taille.y = y;
		}
		tmp_y = 0;
		tmp_x = 0;
        }
	return (taille);
}

void bsq(char **map, int max_x, int max_y)
{
        int c = 0;
	square_pos final = {-2, -1, -1};
	square_pos t = {-2, -1, -1};
	
	for (int i = 0; i < max_y; i = i + 1) {
		for (;c < max_x; c = c + 1) {
			if (map[i][c] == '.') {
				t = find_square(map, i, c, max_y);
				if (t.size > final.size) {
					final.size = t.size;
					final.x = t.x;
					final.y = t.y;
				}
		        }
		}
		c = 0;
	}
	print_map(map, final);
}

int main(int argc, char *argv[])
{
	char **result = NULL;
	int max_x = get_line_nbr(argv[1]);
	int max_y = get_colon_nbr(argv[1]);
	(void)argc;

	result = create_map(result, argv[1], max_x, max_y);
	bsq(result, max_y, max_x);
	free(result);
	return (0);
}
