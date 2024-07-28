/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 07:07:27 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/28 21:11:07 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_create_thread(t_philo *philo, t_arg *arg)
{
	if (pthread_create(&(philo->thread), NULL, routine_main, philo) != 0)
	{
		free_philo(philo, arg);
		free_arg(arg);
		return (1);
	}
	return (0);
}

static int	ft_thread_join(t_arg *arg, t_philo *philo, t_philo *head)
{
	philo = head;
	while (philo->id < arg->nb_philo)
	{
		if (pthread_join(philo->thread, NULL) != 0)
		{
			printf("Error while joining thread\n");
			break ;
		}
		if (philo->arg->nb_philo > 1)
			philo = philo->next;
		else
			break ;
		if (philo == head)
			break ;
	}
	pthread_join(philo->thread, NULL);
	philo = head;
	free_philo(philo, arg);
	free_arg(arg);
	return (0);
}

int	main(int argc, char **argv)
{
	t_arg	*arg;
	t_philo	*philo;
	t_philo	*head;

	if (ft_parsing(argc, argv))
		return (0);
	arg = define_arg(argc, argv);
	if (!arg)
		return (0);
	philo = define_philo(arg);
	if (!philo)
		return (free_arg(arg));
	head = philo;
	while (philo)
	{
		if (ft_create_thread(philo, arg))
			return (0);
		if (!(philo->arg->nb_philo > 1))
			break ;
		philo = philo->next;
		usleep(100);
		if (philo == head)
			break ;
	}
	return (ft_thread_join(arg, philo, head));
}
