NAME := ft_virus

CC := gcc

CPATH = src/
HPATH = inc/
OPATH = obj/

CFILES = \
	 main.c \
	 syscall.c \
	 binary_finder.c


OFILES = $(CFILES:.c=.o)

OBJ = $(addprefix $(OPATH), $(OFILES))


HFILES = inc/ft_virus.h

INC = $(addprefix -I./, $(HPATH))

.PHONY: all install clean fclean re test

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
	mkdir -p $(OPATH)
	$(CC) -g $(INC) $< -c -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
