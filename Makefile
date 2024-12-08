NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
SRCS = pcloses.c pipex_utils.c pipex.c

OBJDIR = obj
SRCDIR = src
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
LIBFT = ./libft
INCLUDE = -I./includes/

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)/libft.a 
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -lft -o $(NAME)

$(LIBFT)/libft.a:
	@make -C $(LIBFT)


$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	@make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re