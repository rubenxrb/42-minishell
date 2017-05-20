MAIN = minishell

CC = gcc
RM = /bin/rm
CFLAGS = -Wall -Werror -Wextra

INC = -Iinc -Isrc/libft/inc -Isrc/libft/src/get_next_line/inc #add ft_printf

SDIR = ./src/
SHLL = ./src/sh/
SBIN = ./src/bin/
ODIR = ./obj/
OSHD = ./obj/sh/
OBND = ./obj/bin/
BDIR = ./bin/
LDIR = $(SDIR)libft/
LIBFT = $(LDIR)libft.a
LNK = -L$(LDIR) -lft

SRCN = prompt.c utils.c cmd_parse.c	\
	background.c
BLTN = ft_cat.c ft_echo.c ft_env.c ft_cd.c

SOBJN = $(SRCN:.c=.o)
OBLTN = $(BLTN:.c=.o)
SRC :=	$(addprefix $(SHLL),$(SRCN))
BLT =	$(addprefix $(SBIN),$(BLTN))
SOBJ =	$(addprefix $(OSHD),$(SOBJN))
BOBJ =	$(addprefix $(OBND),$(OBLTN))

all: $(MAIN)

$(MAIN): lib mkobj $(SOBJ) $(BOBJ)
	$(CC) $(CFLAGS) -o $(MAIN) $(SDIR)main.c $(LNK) $(SOBJ) $(BOBJ) $(INC)
	@echo "[ ./minishell ] compiled!"

obj/sh/%.o:src/sh/%.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

obj/bin/%.o:src/bin/%.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

mkobj:
	@mkdir -p $(ODIR)
	@mkdir -p $(OSHD)
	@mkdir -p $(OBND)

lib:
	@make -C $(LDIR)

clean:
	@make -C $(LDIR) clean
	@$(RM) -rf $(ODIR)
	@echo "[ ./obj/ ] removed"

fclean: clean
	@make -C $(LDIR) fclean
	@$(RM) -rf $(NAME)
	@echo "[ ./minishell ] removed"

re: fclean all
.PHONY: all clean fclean re
