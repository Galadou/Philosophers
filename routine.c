/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 05:51:08 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/21 13:53:21 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	routine_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->arg->mutex_printf);
	gettimeofday(&philo->time_now, NULL);
	printf("%ld %d is sleeping\n", ((philo->time_now.tv_sec
				- philo->arg->time_start.tv_sec) * 1000
			+ (philo->time_now.tv_usec - philo->arg->time_start.tv_usec)
			/ 1000), philo->id);
	pthread_mutex_unlock(philo->arg->mutex_printf);
	gettimeofday(&philo->time_start_sleep, NULL);
	while ((philo->time_now.tv_sec * 1000000 + philo->time_now.tv_usec)
		< (philo->time_start_sleep.tv_sec * 1000000
			+ philo->time_start_sleep.tv_usec + philo->arg->time_sleep
			* 1000))
	{
		usleep(128);
		gettimeofday(&philo->time_now, NULL);
		if (philo->arg->is_someone_died || ft_am_i_dead(philo)
			|| (philo->arg->is_nb_eat && philo->arg->nb_finish_eat
				== philo->arg->nb_philo))
			return ;
		gettimeofday(&philo->time_now, NULL);
	}
}

static void	routine_think(t_philo *philo)
{
	pthread_mutex_lock(philo->arg->mutex_printf);
	gettimeofday(&philo->time_now, NULL);
	printf("%ld %d is thinking\n", ((philo->time_now.tv_sec
				- philo->arg->time_start.tv_sec) * 1000
			+ (philo->time_now.tv_usec - philo->arg->time_start.tv_usec)
			/ 1000), philo->id);
	pthread_mutex_unlock(philo->arg->mutex_printf);
}

static int	routine_exec(t_philo *philo)
{
	routine_eat(philo);
	if (philo->arg->is_someone_died || (philo->arg->is_nb_eat
			&& philo->arg->nb_finish_eat == philo->arg->nb_philo))
		return (1);
	routine_sleep(philo);
	if (philo->arg->is_someone_died || (philo->arg->is_nb_eat
			&& philo->arg->nb_finish_eat == philo->arg->nb_philo))
		return (1);
	routine_think(philo);
	if (philo->arg->is_someone_died || (philo->arg->is_nb_eat
			&& philo->arg->nb_finish_eat == philo->arg->nb_philo))
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
			while (1)
			{
				usleep(128);
				gettimeofday(&philo->time_now, NULL);
				if (ft_check_dead(philo))
					return (0);
				gettimeofday(&philo->time_now, NULL);
			}
		}
		if (routine_exec(philo) == 1)
			return (0);
	}
	return (0);
}
