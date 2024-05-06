#include "philo.h"

void	free_lst(t_philo *list)
{
	t_philo *buffer;

	buffer = list->next;
	free(list);
	while (buffer)
	{
		list = buffer;
		buffer = buffer->next;
		free(list);
	}
}

void	free_linked_lst(t_philo *list, t_arg *arg)
{
	t_philo *buffer;

	buffer = list->next;
	free(list);
	while (buffer->id != arg->nb_philo)
	{
		list = buffer;
		buffer = buffer->next;
		free(list);
	}
	list = buffer;
	buffer = buffer->next;
	free(list);
}

void	free_lst_and_exit(t_philo *list)
{
	free_lst(list);
	exit(1);
}

void	free_philo(t_philo *list, t_arg *arg)
{
	t_philo *buffer;

	buffer = list;
	while (buffer->id != arg->nb_philo)
	{
		pthread_mutex_destroy(buffer->mutex_fork);
		free(buffer->mutex_fork);
		buffer = buffer->next;
	}
	pthread_mutex_destroy(buffer->mutex_fork);
	free(buffer->mutex_fork);
	buffer = buffer->next;
	free_linked_lst(list, arg);
}

