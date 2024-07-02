/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_dead.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:44:42 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/02 15:00:32 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_am_i_dead(t_philo *philo)
{
	gettimeofday(&philo->time_now, NULL);
	if (philo->time_now.tv_usec - philo->time_last_eat.tv_usec > philo->arg->time_death * 1000)
	{
		pthread_mutex_lock(philo->arg->mutex_s_died);
		philo->arg->is_someone_died = true;
		pthread_mutex_unlock(philo->arg->mutex_s_died);
		pthread_mutex_lock(philo->arg->mutex_printf);
		printf("{%ld} | %d is dead\n", ((abso((philo->arg->time_start.tv_usec / 1000) - (philo->time_now.tv_usec / 1000))) + abso((philo->arg->time_start.tv_sec * 1000) - (philo->time_now.tv_sec * 1000))), philo->id);
		pthread_mutex_unlock(philo->arg->mutex_printf);
		return (true);
	}
	return (false);
}
