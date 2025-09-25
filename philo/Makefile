NAME = philo

CC = cc
CFLAGS = -g -Wall -Werror -Wextra -pthread
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

OBJS_DIR = ../objs

LIB_DIR = ../libft
LIBFT = $(LIB_DIR)/libft.a


PHILO_DIR = ./
PHILO_SRC = $(wildcard $(PHILO_DIR)/*.c)

PHILO_OBJ = $(patsubst $(PHILO_DIR)/%.c,$(OBJS_DIR)/%.o,$(PHILO_SRC))

INCLUDE_DIRS = -I$(LIB_DIR) -I$(PHILO_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(PHILO_OBJ)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -o $@ $(PHILO_OBJ) -L$(LIB_DIR) -lft -lpthread

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(PHILO_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

clean:
	rm -f $(PHILO_OBJ)
	$(MAKE) clean -C $(LIB_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
