/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 21:14:15 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/30 14:51:31 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	routine_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->mutex_printf);
	if (ft_check_dead(philo, false, false))
	{
		pthread_mutex_unlock(&philo->arg->mutex_printf);
		return (1);
	}
	gettimeofday(&philo->time_now, NULL);
	printf("%ld %d is thinking\n", ((philo->time_now.tv_sec
				- philo->arg->time_start.tv_sec) * 1000
			+ (philo->time_now.tv_usec - philo->arg->time_start.tv_usec)
			/ 1000), philo->id);
	pthread_mutex_unlock(&philo->arg->mutex_printf);
	return (0);
}

static int	exec_think(t_philo	*philo)
{
	if (philo->arg->is_someone_died || (philo->arg->is_nb_eat
			&& philo->arg->nb_finish_eat == philo->arg->nb_philo))
	{
		pthread_mutex_unlock(&philo->arg->mutex_s_died);
		pthread_mutex_unlock(&philo->arg->mutex_finish_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->arg->mutex_s_died);
	pthread_mutex_unlock(&philo->arg->mutex_finish_eat);
	//usleep(1000);
	if (routine_think(philo))
		return (1);
	pthread_mutex_lock(&philo->arg->mutex_finish_eat);
	pthread_mutex_lock(&philo->arg->mutex_s_died);
	if (philo->arg->is_someone_died || (philo->arg->is_nb_eat
			&& philo->arg->nb_finish_eat == philo->arg->nb_philo))
	{
		pthread_mutex_unlock(&philo->arg->mutex_s_died);
		pthread_mutex_unlock(&philo->arg->mutex_finish_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->arg->mutex_s_died);
	pthread_mutex_unlock(&philo->arg->mutex_finish_eat);
	return (0);
}

static int	routine_exec(t_philo *philo)
{
	routine_eat(philo);
	pthread_mutex_lock(&philo->arg->mutex_finish_eat);
	pthread_mutex_lock(&philo->arg->mutex_s_died);
	if (philo->arg->is_someone_died || (philo->arg->is_nb_eat
			&& philo->arg->nb_finish_eat == philo->arg->nb_philo))
	{
		pthread_mutex_unlock(&philo->arg->mutex_s_died);
		pthread_mutex_unlock(&philo->arg->mutex_finish_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->arg->mutex_s_died);
	pthread_mutex_unlock(&philo->arg->mutex_finish_eat);
	routine_sleep(philo);
	pthread_mutex_lock(&philo->arg->mutex_finish_eat);
	pthread_mutex_lock(&philo->arg->mutex_s_died);
	if (exec_think(philo))
		return (1);
	return (0);
}

void	*routine_main(void *pt)
{
	t_philo	*philo;

	philo = (t_philo *)pt;
	if (!(philo->id & 1))
		usleep(1000);
	while (1)
	{
		if (philo->arg->nb_philo == 1)
		{
			pthread_mutex_lock(&philo->mutex_l_fork);
			printf("%ld %d has taken a fork\n", ((philo->time_now.tv_sec
						- philo->arg->time_start.tv_sec) * 1000
					+ (philo->time_now.tv_usec - philo->arg->time_start.tv_usec)
					/ 1000), philo->id);
			while (1)
			{
				usleep(128);
				if (ft_check_dead(philo, true, false))
					return (0);
			}
		}
		if (routine_exec(philo) == 1)
			return (0);
	}
	return (0);
}
