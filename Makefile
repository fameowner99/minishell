NAME = minishell

CC = gcc

FLAGS = -Wall -Wextra -Werror 

RM = rm -f

HEADERPATH = -I ./inc

SRC = src/main.c src/minishell.c src/parse_line.c src/parse_variable.c src/parse_cd_arg.c src/parse_echo.c src/parse_ls.c

LIB_DIR = libft/

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_DIR) all
	$(CC) $(FLAGS) $(OBJ) -o $@ -L./libft/ -lft 
	@echo "minishell done."

%.o: %.c
	$(CC) $(HEADERPATH) $(FLAGS)  -o $@ -c $<

clean:
	@make clean -C $(LIB_DIR)
	$(RM) $(OBJ)

fclean: clean
	@make fclean -C $(LIB_DIR)
	$(RM) $(NAME)

re: fclean all
