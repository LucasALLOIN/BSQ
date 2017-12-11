##
## EPITECH PROJECT, 2017
## Project bsq
## File description:
## Build bsq binary.
##

SRC	=	source/main.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Werror -Wextra -W -Wall -Wparentheses -Wsign-compare -Wpointer-sign -Wuninitialized -Wunused-but-set-variable -I ./include/ -L lib/my -lmy -O3

NAME	=	bsq

CC	=	gcc

all:	$(NAME)

$(NAME):	$(OBJ)
		make -C lib/my
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
