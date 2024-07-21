CC = cc 

CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=thread


SRC = ph.c ft_init.c rotini.c utils.c get_set.c

NAME = philo

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) ph.h
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME) 

re : clean fclean all

.PHONY : all clean fclean re
