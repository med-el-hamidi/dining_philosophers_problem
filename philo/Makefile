NAME := philo

CC := cc
CFLGS := -Wall -Wextra -Werror -fsanitize=thread
RM := rm -f

HEADER := philo.h
SRCS :=	input.c \
		init.c \
		philo.c \
		monitor.c \
		free.c \
		utils.c \
		main.c

OBJCS := $(SRCS:.c=.o)

$(NAME): $(OBJCS)
	$(CC) $(CFLGS) -pthread $^ -o $@

%.o:%.c $(HEADER)
	$(CC) $(CFLGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJCS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONEY: clean


