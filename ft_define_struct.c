/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 21:13:21 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/28 21:13:23 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_arg	*define_arg(int argc, char **argv)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg));
	gettimeofday(&arg->time_start, NULL);
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
	arg->nb_finish_eat = 0;
	arg->fork_reverse = ft_atoi(argv[1]);
	pthread_mutex_init(&arg->mutex_reverse, NULL);
	pthread_mutex_init(&arg->mutex_finish_eat, NULL);
	pthread_mutex_init(&arg->mutex_s_died, NULL);
	pthread_mutex_init(&arg->mutex_printf, NULL);
	return (arg);
}

static t_philo	*ft_lstnew_philo(int id, t_arg *arg)
{
	t_philo			*head;

	head = malloc(sizeof(t_philo));
	if (!head)
		return (NULL);
	head->arg = arg;
	head->id = id;
	pthread_mutex_init(&head->mutex_l_fork, NULL);
	head->mutex_r_fork = NULL;
	head->time_last_eat = arg->time_start;
	gettimeofday(&head->time_now, NULL);
	head->time_eating = 0;
	head->time_sleep = 0;
	head->nb_eat = 0;
	head->next = NULL;
	head->time_start_sleep = arg->time_start;
	return (head);
}

static t_philo	*ft_set_r_fork(t_philo *head)
{
	t_philo	*buffer;

	buffer = head;
	buffer->mutex_r_fork = &buffer->next->mutex_l_fork;
	buffer = buffer->next;
	while (buffer != head)
	{
		buffer->mutex_r_fork = &buffer->next->mutex_l_fork;
		buffer = buffer->next;
	}
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
			return (free_lst(head));
	}
	if (arg->nb_philo == 1)
		return (head);
	buffer = head;
	id++;
	while (id < arg->nb_philo + 1)
	{
		buffer->next = ft_lstnew_philo(id, arg);
		if (buffer->next == NULL)
			return (free_lst(head));
		id++;
		buffer = buffer->next;
	}
	buffer->next = head;
	return (ft_set_r_fork(head));
}
