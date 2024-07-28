COMP		= gcc
CFLAGS		= -Wall -Werror -Wextra -lpthread -g
INCLUDE		= philo.h
NAME		= philo


SRC			=	main.c\
				ft_atoi.c\
				ft_define_struct.c\
				ft_ultimate_free.c\
				ft_routine.c \
				ft_philo_dead.c \
				ft_routine_eat.c \
				ft_parsing.c \
				ft_routine_sleep.c


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
