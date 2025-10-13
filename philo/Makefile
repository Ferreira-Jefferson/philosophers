NAME = philo

CC = cc
CFLAGS = -g -Wall -Werror -Wextra -pthread
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

PHILO_DIR = ./
OBJS_DIR = ../objs

PHILO_SRC = core.c libft.c monitor.c philosophers.c utils_core.c utils_init.c utils.c

PHILO_OBJ = $(addprefix $(OBJS_DIR)/, $(PHILO_SRC:.c=.o))

INCLUDE_DIRS = -I$(PHILO_DIR)

all: $(NAME)

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

.PHONY: all clean fclean re
