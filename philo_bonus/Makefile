NAME = philo_bonus

CC = cc
CFLAGS = -g -Wall -Werror -Wextra -pthread
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

OBJS_DIR = ../objs



PHILO_DIR = ./
PHILO_SRC = $(wildcard $(PHILO_DIR)/*.c)

PHILO_OBJ = $(patsubst $(PHILO_DIR)/%.c,$(OBJS_DIR)/%.o,$(PHILO_SRC))

INCLUDE_DIRS = -I$(PHILO_DIR)

all: bonus

$(NAME): $(PHILO_OBJ)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -o $@ $(PHILO_OBJ) -lpthread

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(PHILO_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

bonus: $(NAME)

clean:
	rm -f $(PHILO_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
