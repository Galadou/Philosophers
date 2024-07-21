/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_eat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 07:45:26 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/21 13:43:18 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_dead(t_philo *philo)
{
	if (ft_am_i_dead(philo) || philo->arg->is_someone_died
		|| (philo->arg->is_nb_eat && philo->arg->nb_finish_eat
			== philo->arg->nb_philo))
	{
		pthread_mutex_unlock(philo->mutex_fork);
		if (philo->arg->nb_philo > 1)
			pthread_mutex_unlock(philo->next->mutex_fork);
		return (1);
	}
	return (0);
}

static int	ft_check_philo(t_philo *philo)
{
	if (ft_check_dead(philo))
		return (1);
	pthread_mutex_lock(philo->arg->mutex_printf);
	gettimeofday(&philo->time_now, NULL);
	printf("%ld %d has taken a fork\n", ((philo->time_now.tv_sec
				- philo->arg->time_start.tv_sec) * 1000
			+ (philo->time_now.tv_usec - philo->arg->time_start.tv_usec)
			/ 1000), philo->id);
	pthread_mutex_unlock(philo->arg->mutex_printf);
	return (0);
}

static void	routine_take_fork(t_philo *philo)
{
	gettimeofday(&philo->time_last_eat, NULL);
	philo->nb_eat++;
	if (philo->arg->is_nb_eat && philo->nb_eat == philo->arg->nb_eat)
	{
		pthread_mutex_lock(philo->arg->mutex_finish_eat);
		philo->arg->nb_finish_eat++;
		pthread_mutex_unlock(philo->arg->mutex_finish_eat);
	}
	pthread_mutex_unlock(philo->mutex_fork);
	pthread_mutex_unlock(philo->next->mutex_fork);
}

static void	routine_exec(t_philo *philo)
{
	pthread_mutex_lock(philo->arg->mutex_printf);
	gettimeofday(&philo->time_now, NULL);
	printf("%ld %d is eating\n", ((philo->time_now.tv_sec
				- philo->arg->time_start.tv_sec) * 1000
			+ (philo->time_now.tv_usec - philo->arg->time_start.tv_usec)
			/ 1000), philo->id);
	pthread_mutex_unlock(philo->arg->mutex_printf);
	if (ft_check_dead(philo))
		return ;
	gettimeofday(&philo->time_start_eat, NULL);
	gettimeofday(&philo->time_now, NULL);
	while (philo->time_now.tv_sec * 1000000 + philo->time_now.tv_usec
		< (philo->time_start_eat.tv_sec * 1000000)
		+ philo->time_start_eat.tv_usec + (philo->arg->time_eat * 1000))
	{
		usleep(128);
		gettimeofday(&philo->time_now, NULL);
		if (ft_check_dead(philo))
			return ;
		gettimeofday(&philo->time_now, NULL);
	}
	routine_take_fork(philo);
	return ;
}

void	routine_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->mutex_fork);
		if (ft_check_philo(philo))
			return ;
		pthread_mutex_lock(philo->next->mutex_fork);
		if (ft_check_philo(philo))
			return ;
	}
	else
	{
		pthread_mutex_lock(philo->next->mutex_fork);
		if (ft_check_philo(philo))
			return ;
		pthread_mutex_lock(philo->mutex_fork);
		if (ft_check_philo(philo))
			return ;
	}
	if (ft_check_dead(philo))
		return ;
	routine_exec(philo);
}
