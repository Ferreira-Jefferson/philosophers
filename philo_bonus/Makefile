NAME = philo_bonus

CC = cc
CFLAGS = -g -Wall -Werror -Wextra -pthread
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

PHILO_DIR = ./
OBJS_DIR = ../objs

PHILO_SRC = core_bonus.c libft_bonus.c philosophers_bonus.c utils_core_bonus.c utils_init_bonus.c utils_bonus.c

PHILO_OBJ = $(addprefix $(OBJS_DIR)/, $(PHILO_SRC:.c=.o))

INCLUDE_DIRS = -I$(PHILO_DIR)

all: bonus

bonus: $(NAME)

$(NAME): $(PHILO_OBJ)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -o $@ $(PHILO_OBJ)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(PHILO_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

clean:
	rm -f $(PHILO_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
