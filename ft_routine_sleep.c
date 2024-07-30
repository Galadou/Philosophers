/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine_sleep.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 21:12:32 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/30 16:10:07 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	print_sleeping(t_philo *philo)
{
	usleep(1000);
	if (ft_check_dead(philo, false, false))
		return (1);
	pthread_mutex_lock(&philo->arg->mutex_printf);
	gettimeofday(&philo->time_now, NULL);
	printf("%ld %d is sleeping\n", ((philo->time_now.tv_sec
				- philo->arg->time_start.tv_sec) * 1000
			+ (philo->time_now.tv_usec - philo->arg->time_start.tv_usec)
			/ 1000), philo->id);
	pthread_mutex_unlock(&philo->arg->mutex_printf);
	return (0);
}

void	routine_sleep(t_philo *philo)
{
	if (print_sleeping(philo))
		return ;
	gettimeofday(&philo->time_start_sleep, NULL);
	while ((philo->time_now.tv_sec * 1000000 + philo->time_now.tv_usec)
		< (philo->time_start_sleep.tv_sec * 1000000
			+ philo->time_start_sleep.tv_usec + philo->arg->time_sleep
			* 1000))
	{
		usleep(128);
		gettimeofday(&philo->time_now, NULL);
		pthread_mutex_lock(&philo->arg->mutex_finish_eat);
		pthread_mutex_lock(&philo->arg->mutex_s_died);
		if (philo->arg->is_someone_died || ft_am_i_dead(philo)
			|| (philo->arg->is_nb_eat && philo->arg->nb_finish_eat
				== philo->arg->nb_philo))
		{
			pthread_mutex_unlock(&philo->arg->mutex_s_died);
			pthread_mutex_unlock(&philo->arg->mutex_finish_eat);
			return ;
		}
		pthread_mutex_unlock(&philo->arg->mutex_s_died);
		pthread_mutex_unlock(&philo->arg->mutex_finish_eat);
		gettimeofday(&philo->time_now, NULL);
	}
}
