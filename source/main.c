/*
** EPITECH PROJECT, 2017
** Project bsq
** File description:
** Main file.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "main.h"

int get_nbr_size(int nb)
{
	int i = 0;

	while (nb > 9) {
		i = i + 1;
		nb /= 10;
	}
	return (i);
}

int get_line_nbr(char *filename)
{
	int file = open(filename, O_RDONLY);
	char buffer[10];
	int res;

	read(file, buffer, 10);
	res = my_getnbr(buffer);
	close(file);
	return (res);
}

int get_colon_nbr(char *filename, int max_y)
{
	int file = open(filename, O_RDONLY);
	struct stat sb;
	long long size;
	char *buffer;
	int i = max_y + 2;
	int z = 0;

	stat(filename, &sb);
	size = sb.st_size;
	buffer = malloc(size);
	read(file, buffer, size);
	for (; buffer[i] != '\n'; z = z + 1, i = i + 1);
	close(file);
	free(buffer);
	return (z);
}

char **create_map(char **result, char *filename, int x, int y)
{
	int file = open(filename, O_RDONLY);
	struct stat sb;
	char *buffer;
	int c = 0;
	int j = get_nbr_size(x);
	int k = 0;

        stat(filename, &sb);
	buffer = malloc(sb.st_size);
	read(file, buffer, sb.st_size);
	buffer = buffer + j + 2;
	result = malloc(sizeof(char *) * x + 1);
	for (int i = 0; i < x; i = i + 1, c = 0) {
		result[i] = malloc(y + 1);
		for (; c < y; c = c + 1) {
			result[i][c] = buffer[k];
			k += 1;
		}
		k += 1;
		read(file, buffer, 1);
	}
	free(buffer - j - 2);
	return (result);
}

void print_map(char **map, square_pos square, int x)
{
	for (int y = square.y; square.y + square.size > y; y = y + 1) {
		for (int x = square.x; square.x + square.size > x; x = x + 1) {
			map[y][x] = 'x';
		}
	}
	for (int i = 0; map[i] != NULL; i = i + 1, my_putchar('\n'))
		write(1, map[i], x);
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
			ctc += 1;
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
	print_map(map, final, max_x);
}

int main(int argc, char *argv[])
{
	char **result = NULL;
	int max_x = get_line_nbr(argv[1]);
	int max_y = get_colon_nbr(argv[1], get_nbr_size(max_x));
	(void)argc;

	result = create_map(result, argv[1], max_x, max_y);
	bsq(result, max_y, max_x);
	free(result);
	return (0);
}
