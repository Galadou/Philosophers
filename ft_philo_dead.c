/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_dead.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 08:56:16 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/30 15:45:00 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_am_i_dead(t_philo *philo)
{
	gettimeofday(&philo->time_now, NULL);
	if ((philo->time_now.tv_sec * 1000000 + philo->time_now.tv_usec)
		> (philo->time_last_eat.tv_sec * 1000000 + philo->time_last_eat.tv_usec
			+ philo->arg->time_death * 1000))
	{
		if (philo->arg->is_someone_died == false)
		{
			pthread_mutex_lock(&philo->arg->mutex_printf);
			printf("%ld %d died\n", ((philo->time_now.tv_sec
						- philo->arg->time_start.tv_sec) * 1000
					+ (philo->time_now.tv_usec
						- philo->arg->time_start.tv_usec) / 1000), philo->id);
			pthread_mutex_unlock(&philo->arg->mutex_printf);
		}
		philo->arg->is_someone_died = true;
		return (true);
	}
	return (false);
}
