/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultimate_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 06:00:25 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/28 12:43:30 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*free_lst(t_philo *list)
{
	t_philo	*buffer;

	buffer = list->next;
	free(list);
	while (buffer)
	{
		list = buffer;
		buffer = buffer->next;
		free(list);
	}
	return (NULL);
}

void	free_linked_lst(t_philo *list, t_arg *arg)
{
	t_philo	*buffer;

	if (list->arg->nb_philo == 1)
	{
		free(list);
		return ;
	}
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

void	free_philo(t_philo *list, t_arg *arg)
{
	t_philo	*buffer;

	buffer = list;
	while (buffer->id != arg->nb_philo)
	{
		pthread_mutex_destroy(&buffer->mutex_fork);
		// free(buffer->mutex_fork);
		if (buffer->arg->nb_philo == 1)
		{
			free_linked_lst(list, arg);
			return ;
		}
		buffer = buffer->next;
	}
	pthread_mutex_destroy(&buffer->mutex_fork);
	// free(buffer->mutex_fork);
	buffer = buffer->next;
	free_linked_lst(list, arg);
}

int	free_arg(t_arg *arg)
{
	if (arg)
	{
		pthread_mutex_destroy(arg->mutex_finish_eat);
		pthread_mutex_destroy(arg->mutex_printf);
		pthread_mutex_destroy(arg->mutex_s_died);
		free(arg->mutex_finish_eat);
		free(arg->mutex_printf);
		free(arg->mutex_s_died);
		free(arg);
	}
	return (0);
}
