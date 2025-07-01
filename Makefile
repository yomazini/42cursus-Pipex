NAME = pipex
BONUS_NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

SRCS = src/pipex.c src/tools.c src/tools1.c
OBJS = $(SRCS:.c=.o)
HEADERS = src/pipex.h 

SRCS_BONUS = src_bonus/pipex_bonus.c src_bonus/tools_bonus.c src/tools.c src/tools1.c 
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
HEADERS_BONUS = src_bonus/pipex_bonus.h

LIBFT_DIR = lib
LIBFT = $(LIBFT_DIR)/libft.a


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT)

bonus: $(OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(BONUS_NAME) $(LIBFT)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c $(HEADERS) $(HEADERS_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all
