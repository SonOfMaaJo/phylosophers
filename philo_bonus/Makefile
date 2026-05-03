NAME        = philo
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -pthread
INCLUDES    = -I includes

SRCS_DIR    = srcs/
OBJS_DIR    = objs/

SRCS_FILES  = ft_atoll_bonus.c \
              inits_bonus.c \
              main_bonus.c \
              threads_utils_bonus.c \
              time_utils_bonus.c \
              utils_bonus.c \
              valids_bonus.c \
			  ft_strlen_bonus.c \
			  ft_strlcat_bonus.c \
			  ft_strdup_bonus.c \
			  ft_itoa_bonus.c

SRCS        = $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS        = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

bonus : all

re: fclean all

debug: CFLAGS += -g3 -fsanitize=thread
debug: re

.PHONY: all clean fclean re debug
