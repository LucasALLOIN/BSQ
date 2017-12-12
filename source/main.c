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

void find_x(char **map, int *tab)
{
	if (tab[0] + tab[5] + 1 >= tab[7])
		tab[4] = 0;
	while (tab[3] > tab[1]) {
		if (map[tab[5] + tab[0]][tab[6] + tab[1]] != '.') {
			tab[4] = 0;
			tab[3] = tab[3] - 1;
		}
		tab[1] += 1;
	}
	tab[1] = 0;
	tab[0] += 1;
}

square_pos find_square(char **map, int y, int x, int max_y)
{
	int tab[8] = {0, 0, 0, 0, 1, y, x , max_y};
	square_pos taille = {-2, -1, -1};

        for (;tab[4]; tab[0] = 0, tab[1] = 0) {
		if (map[tab[5]][tab[6] + 1] == '.') {
	        	tab[2] = tab[2] + 1;
			tab[3] += 1;
		} else {
			tab[4] = 0;
			tab[3] += 1;
		}
	        while (tab[2] > tab[0])
			find_x(map, tab);
		if (taille.size < tab[3]) {
			taille.size = tab[3];
			taille.x = tab[6];
			taille.y = tab[5];
		}
        }
	return (taille);
}

square_pos find_final(square_pos final, char **map, int *tab, int i)
{
	square_pos t = {-2, -1, -1};

	if (map[i][tab[0]] == '.') {
		t = find_square(map, i, tab[0], tab[2]);
		if (t.size > final.size) {
			final.size = t.size;
			final.x = t.x;
			final.y = t.y;
		}
	}
	return (final);
}

void bsq(char **map, int max_x, int max_y)
{
	int tab[3] = {0, max_x, max_y};
	square_pos final = {-2, -1, -1};
	
	for (int i = 0; i < tab[2]; i = i + 1) {
		for (;tab[0] < tab[1] && final.size != tab[2] \
			     && final.size && tab[1]; tab[0] += 1) {
			final = find_final(final, map, tab, i);
		}
		tab[0] = 0;
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
