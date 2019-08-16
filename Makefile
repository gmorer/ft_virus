NAME := ft_virus

CC := gcc

CFLAGS = -masm=intel

CPATH = src/
HPATH = inc/
OPATH = obj/

CFILES = \
	 main.c \
	 syscall.c \
	 binary_finder.c\
	 libft.c\
	 inject.c

OFILES = $(CFILES:.c=.o)

OBJ = $(addprefix $(OPATH), $(OFILES))

HFILES = inc/ft_virus.h

INC = $(addprefix -I./, $(HPATH))

LINKER := ld
LINKER_CONF := linker.ld
LINKER_FLAGS := -T $(LINKER_CONF)

.PHONY: all install clean fclean re test

all: $(NAME)

$(NAME): $(OBJ)
	$(LD) $(LINKER_FLAGS) $(OBJ) -o $(NAME)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
	mkdir -p $(OPATH)
	$(CC) $(CFLAGS) -g $(INC) $< -c -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
