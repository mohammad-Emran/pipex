CC = cc
NAME= pipex
CFLAGS = -Wall -Werror -Wextra 
SRCS = pipex.c pipex_utils.c pcloses.c

OBJECTS = $(SRCS:.c=.o)
LIBFT_DIR = ./libft
LIBFT= $(LIBFT_DIR)/libft.a
INCLUDE= -I./

all:$(NAME)

$(NAME): $(OBJECTS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJECTS) -L$(LIBFT_DIR) -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
clean: 
	rm -f $(OBJECTS)
	@make clean -C $(LIBFT_DIR)
fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
