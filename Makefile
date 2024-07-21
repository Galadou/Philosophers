COMP		= gcc
CFLAGS		= -Wall -Werror -Wextra -lpthread -g
INCLUDE		= philo.h
NAME		= philo


SRC			=	main.c\
				ft_atoi.c\
				define_struct.c\
				ultimate_free.c\
				routine.c \
				ft_philo_dead.c \
				routine_eat.c


OBJS=$(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
				echo $(OBJS)
				@$(COMP) $(CFLAGS) $(OBJS) -o $(NAME)
				@if [ $$? -eq 0 ]; then \
				echo "\033[32;1mCompilation successful!\033[0m"; \
				fi

%.o : %.c
		$(COMP) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean  re all
