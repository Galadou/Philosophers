#include "philo.h"

void	define_arg(t_arg *arg, int argc, char **argv)
{
	arg->time_start = gettimeofday(NULL, NULL);
	arg->nb_philo = ft_atoi(argv[1]);
	arg->time_death = ft_atoi(argv[2]);
	arg->time_eat = ft_atoi(argv[3]);
	arg->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		arg->nb_eat = ft_atoi(argv[5]);
		arg->is_nb_eat = true;
	}
	else
		arg->is_nb_eat = false;
	arg->is_someone_died = 0;
	arg->mutex_s_died = malloc(sizeof(pthread_mutex_t));
	arg->mutex_printf = malloc(sizeof(pthread_mutex_t));

	pthread_mutex_init(arg->mutex_s_died, NULL);
	pthread_mutex_init(arg->mutex_printf, NULL);
}

static t_philo	*ft_lstnew_philo(int id, t_arg *arg)
{
	t_philo *head;

	head = malloc(sizeof(t_philo));
	if (!head)
		exit(1);
	head->id = id;
	head->fork = true;
	head->mutex_fork = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(head->mutex_fork, NULL);
	head->time_last_eat = arg->time_start;
	head->time_eating = 0;
	head->time_sleep = 0;
	head->nb_eat_time = 0;
	head->next = NULL;
	return (head);
}

t_philo	*define_philo(t_arg *arg)
{
	int		id;
	t_philo	*buffer;
	t_philo	*head;

	id = 1;
	if (arg->nb_philo > 0)
	{
		head = ft_lstnew_philo(id, arg);
		if (head == NULL)
			free_lst(head);
	}
	buffer = head;
	id++;
	while (id < arg->nb_philo + 1)
	{
		buffer->next = ft_lstnew_philo(id, arg);
		if (buffer->next == NULL)
			free_lst_and_exit(head);
		id++;
		buffer = buffer->next;
	}
	buffer->next = head;
	return (head);
}
