NAME := Pestilence

CC := gcc
ASM := nasm

CFLAGS = -masm=intel -fno-stack-protector -O0
ifeq ($(OPT), LD)
CFLAGS += -ffunction-sections -nostdlib -D __NO_MAIN__
endif
ifeq ($(LEVEL), DEBUG)
CFLAGS += -D __HELLO__
endif
SFLAGS := -f elf64

CPATH = src/
HPATH = inc/
OPATH = obj/

OBJS = \
	 main.o \
	 syscall.o \
	 crypto.o\
	 libft.o\
	 get_addr.o\
	 process.o\
	 payload.o\
	 binary_finder.o\
	 inject.o\
	 get_infos.o\
	 payload_end.o

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

ifeq ($(OPT), LD)
$(NAME): $(ALL_OBJS)
	$(LD) $(LINKER_FLAGS) $(ALL_OBJS) -o $(NAME)
else
$(NAME): $(ALL_OBJS)
	$(CC) $(CFLAGS) $(ALL_OBJS) -o $(NAME)
endif

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
