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

SRCN = prompt.c utils.c cmd.c background.c
BLTN = ft_cat.c ft_echo.c ft_env.c ft_cd.c	\
	ft_history.c ft_up.c

SOBJN = $(SRCN:.c=.o)
OBLTN = $(BLTN:.c=.o)
SRC :=	$(addprefix $(SHLL),$(SRCN))
BLT :=	$(addprefix $(SBIN),$(BLTN))
SOBJ =	$(addprefix $(OSHD),$(SOBJN))
BOBJ =	$(addprefix $(OBND),$(OBLTN))

all: $(MAIN)

$(MAIN): lib mkobj $(SOBJ) $(BOBJ)
	$(CC) $(CFLAGS) -o $(MAIN) $(SDIR)main.c $(INC) $(SOBJ) $(BOBJ) $(LNK)
	@printf "\x1b[36m[ ./minishell ] <compiled>\n\x1b[0m"

obj/sh/%.o:src/sh/%.c
	$(CC) $(CFLAGS) $(INC) $(LNK) -o $@ -c $<

obj/bin/%.o:src/bin/%.c
	$(CC) $(CFLAGS) $(INC) $(LNK) -o $@ -c $<

mkobj:
	@mkdir -p $(ODIR)
	@mkdir -p $(OSHD)
	@mkdir -p $(OBND)

lib:
	@make -C $(LDIR)

clean:
	@make -C $(LDIR) clean
	@$(RM) -rf $(ODIR)
	@printf "\x1b[31m[./obj/] <removed>\n\x1b[0m"

fclean: clean
	@make -C $(LDIR) fclean
	@$(RM) -rf $(MAIN)
	@printf "\x1b[31m[./minishell] <removed>\n\x1b[0m"

re: fclean all
.PHONY: all clean fclean re
