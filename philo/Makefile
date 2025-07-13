NAME := philo

CC := cc
CFLGS := -Wall -Wextra -Werror -fsanitize=address
RM := rm -f

HEADERS := philo_macros.h philo.h
SRCS :=	error.c\
		input.c \
		input_utils.c \
		utils.c \
		init.c \
		monitor.c \
		philo.c \
		cleanup.c \
		main.c

OBJCS := $(SRCS:.c=.o)

$(NAME): $(OBJCS)
	$(CC) $(CFLGS) -g -pthread $^ -o $@

%.o:%.c $(HEADERS)
	$(CC) $(CFLGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJCS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONEY: clean


