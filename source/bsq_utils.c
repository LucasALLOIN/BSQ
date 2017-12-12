/*
** EPITECH PROJECT, 2017
** utils
** File description:
** utils
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
	for (int i = 0; i < x; i = i + 1, c = 0, k += 1) {
		result[i] = malloc(y + 1);
		for (; c < y; c = c + 1, k += 1)
			result[i][c] = buffer[k];
	}
	free(buffer - j - 2);
	return (result);
}

void print_map(char **map, square_pos square, int x)
{
	for (int y = square.y; square.y + square.size > y; y = y + 1)
		for (int x = square.x; square.x + square.size > x; x = x + 1)
			map[y][x] = 'x';
	for (int i = 0; map[i] != NULL; i = i + 1, my_putchar('\n'))
		write(1, map[i], x);
}
