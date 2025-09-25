NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

OBJ_DIR = objs
UTILS_DIR = utils

MANDATORY_SRC = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
				ft_isprint.c ft_tolower.c ft_toupper.c ft_atoi.c \
				ft_memcmp.c ft_strncmp.c ft_itoa.c ft_strdup.c \
				ft_split.c ft_strchr.c ft_strrchr.c ft_strjoin.c \
				ft_strtrim.c ft_strmapi.c ft_substr.c ft_strnstr.c \
				ft_bzero.c ft_putnbr_fd.c ft_putchar_fd.c ft_putstr_fd.c \
				ft_putendl_fd.c ft_memset.c ft_calloc.c ft_memchr.c \
				ft_memcpy.c ft_memmove.c ft_striteri.c ft_strlen.c \
				ft_strlcpy.c ft_strlcat.c

BONUS_SRC = ft_lstdelone.c ft_lstmap.c ft_lstclear.c \
			ft_lstiter.c ft_lstlast.c ft_lstsize.c \
			ft_lstadd_back.c ft_lstadd_front.c ft_lstnew.c 

EXTRA_SRC = ft_atoi_base.c ft_convert_base.c ft_is_valid_base.c ft_itoa_base.c \
			ft_putunbr_fd.c ft_realloc.c ft_to_free.c ft_count_decimal_places.c \
			ft_isspace.c get_next_line.c ft_printf.c ft_isequal.c ft_is_only_number.c

UTILS_SRC = ft_print_char.c ft_print_hex_lower.c \
			ft_print_hex_upper.c ft_print_int.c \
			ft_print_percent.c ft_print_pointer.c \
			ft_print_string.c ft_print_unsigned.c ft_atol.c \
			ft_free_str_vector.c

UTILS_SRC := $(addprefix $(UTILS_DIR)/, $(UTILS_SRC))

MANDATORY_OBJ = $(MANDATORY_SRC:.c=.o)
BONUS_OBJ     = $(BONUS_SRC:.c=.o)
EXTRA_OBJ     = $(EXTRA_SRC:.c=.o)
UTILS_OBJ     = $(UTILS_SRC:.c=.o)

MANDATORY_OBJ = $(addprefix $(OBJ_DIR)/, $(MANDATORY_SRC:.c=.o))
BONUS_OBJ     = $(addprefix $(OBJ_DIR)/, $(BONUS_SRC:.c=.o))
EXTRA_OBJ     = $(addprefix $(OBJ_DIR)/, $(EXTRA_SRC:.c=.o))
UTILS_OBJ	  = $(addprefix $(OBJ_DIR)/, $(notdir $(UTILS_SRC:.c=.o)))

OBJS = $(UTILS_OBJ) $(MANDATORY_OBJ) $(BONUS_OBJ) $(EXTRA_OBJ)

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $@ $^
 
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

test: $(NAME)
	gcc main.c -L. -lft
	./a.out

re: fclean all

.PHONY: all clean fclean re
