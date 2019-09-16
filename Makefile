NAME := ft_virus

CC := gcc
ASM := nasm

CFLAGS = -masm=intel -ffunction-sections -fno-stack-protector -O0
SFLAGS := -f elf64

CPATH = src/
HPATH = inc/
OPATH = obj/

OBJS = \
	 main.o \
	 syscall.o \
	 binary_finder.o\
	 libft.o\
	 inject.o\
	 get_infos.o\
	 get_addr.o\
	 process.o\
	 crypto.o

ALL_OBJS = $(addprefix $(OPATH), $(OBJS))

HFILES = inc/ft_virus.h

INC = $(addprefix -I./, $(HPATH))

LINKER := ld
LINKER_CONF := linker.ld
LINKER_FLAGS := -T $(LINKER_CONF) 

#.PHONY: all install clean fclean re test

all: $(NAME)

$(OPATH):
	mkdir -p $(OPATH)

$(NAME): $(ALL_OBJS)
	$(LD) $(LINKER_FLAGS) $(ALL_OBJS) -o $(NAME)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
	mkdir -p $(OPATH)
	$(CC) $(CFLAGS) $(INC) $< -c -o $@

$(OPATH)%.o: $(CPATH)%.s $(HFILES)
	mkdir -p $(OPATH)
	$(ASM) $(SFLAGS) $< -o $@

clean:
	rm -f $(ALL_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
