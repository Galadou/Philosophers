/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 07:07:27 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/28 14:23:04 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_thread_join(t_arg *arg, t_philo *philo, t_philo *buffer)
{
	philo = buffer;
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
		if (philo == buffer)
			break ;
	}
	pthread_join(philo->thread, NULL);
	philo = buffer;
	free_philo(philo, arg);
	free_arg(arg);
}

int	main(int argc, char **argv)
{
	t_arg	*arg;
	t_philo	*philo;
	t_philo	*buffer;

	if (ft_parsing(argc, argv))
		return (0);
	arg = define_arg(argc, argv);
	if (!arg)
		return (0);
	philo = define_philo(arg);
	if (!philo)
		return (free_arg(arg));
	buffer = philo;
	while (philo)
	{
		if (pthread_create(&(philo->thread), NULL, routine_main, philo) != 0)
		{
			free_philo(philo, arg);
			free_arg(arg);
			return (0);
		}
		if (philo->arg->nb_philo > 1)
			philo = philo->next;
		else
			break ;
		usleep(1000);
		if (philo == buffer)
			break ;
	}
	ft_thread_join(arg, philo, buffer);
}
