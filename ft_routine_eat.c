/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine_eat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 21:13:49 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/28 21:13:51 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_dead(t_philo *philo, bool l, bool r)
{
	pthread_mutex_lock(&philo->arg->mutex_s_died);
	pthread_mutex_lock(&philo->arg->mutex_finish_eat);
	if (ft_am_i_dead(philo) || philo->arg->is_someone_died
		|| (philo->arg->is_nb_eat && philo->arg->nb_finish_eat
			== philo->arg->nb_philo))
	{
		if (l)
			pthread_mutex_unlock(&philo->mutex_l_fork);
		if (philo->arg->nb_philo > 1 && r)
			pthread_mutex_unlock(philo->mutex_r_fork);
		pthread_mutex_unlock(&philo->arg->mutex_finish_eat);
		pthread_mutex_unlock(&philo->arg->mutex_s_died);
		return (1);
	}
	pthread_mutex_unlock(&philo->arg->mutex_finish_eat);
	pthread_mutex_unlock(&philo->arg->mutex_s_died);
	return (0);
}

static int	ft_check_philo(t_philo *philo, bool l, bool r)
{
	if (ft_check_dead(philo, l, r))
		return (1);
	pthread_mutex_lock(&philo->arg->mutex_printf);
	gettimeofday(&philo->time_now, NULL);
	printf("%ld %d has taken a fork\n", ((philo->time_now.tv_sec
				- philo->arg->time_start.tv_sec) * 1000
			+ (philo->time_now.tv_usec - philo->arg->time_start.tv_usec)
			/ 1000), philo->id);
	pthread_mutex_unlock(&philo->arg->mutex_printf);
	return (0);
}

static void	routine_take_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->arg->mutex_printf);
	if (ft_check_dead(philo, true, true))
		return ;
	gettimeofday(&philo->time_start_eat, NULL);
	gettimeofday(&philo->time_now, NULL);
	while (philo->time_now.tv_sec * 1000000 + philo->time_now.tv_usec
		< (philo->time_start_eat.tv_sec * 1000000)
		+ philo->time_start_eat.tv_usec + (philo->arg->time_eat * 1000))
	{
		usleep(128);
		gettimeofday(&philo->time_now, NULL);
		if (ft_check_dead(philo, true, true))
			return ;
		gettimeofday(&philo->time_now, NULL);
	}
	gettimeofday(&philo->time_last_eat, NULL);
	philo->nb_eat++;
	if (philo->arg->is_nb_eat && philo->nb_eat == philo->arg->nb_eat)
	{
		pthread_mutex_lock(&philo->arg->mutex_finish_eat);
		philo->arg->nb_finish_eat++;
		pthread_mutex_unlock(&philo->arg->mutex_finish_eat);
	}
	pthread_mutex_unlock(&philo->mutex_l_fork);
	pthread_mutex_unlock(philo->mutex_r_fork);
}

static void	routine_exec(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->mutex_l_fork);
		if (ft_check_philo(philo, true, false))
			return ;
		pthread_mutex_lock(philo->mutex_r_fork);
		if (ft_check_philo(philo, true, true))
			return ;
	}
	else
	{
		pthread_mutex_lock(philo->mutex_r_fork);
		if (ft_check_philo(philo, false, true))
			return ;
		pthread_mutex_lock(&philo->mutex_l_fork);
		if (ft_check_philo(philo, true, true))
			return ;
	}
	pthread_mutex_lock(&philo->arg->mutex_printf);
	gettimeofday(&philo->time_now, NULL);
	printf("%ld %d is eating\n", ((philo->time_now.tv_sec
				- philo->arg->time_start.tv_sec) * 1000
			+ (philo->time_now.tv_usec - philo->arg->time_start.tv_usec)
			/ 1000), philo->id);
	routine_take_fork(philo);
}

void	routine_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->mutex_reverse);
	if (philo->arg->fork_reverse == philo->id)
	{
		philo->arg->fork_reverse--;
		if (philo->arg->fork_reverse == 0)
			philo->arg->fork_reverse = philo->arg->nb_philo;
		pthread_mutex_unlock(&philo->arg->mutex_reverse);
		usleep(500);
	}
	else
		pthread_mutex_unlock(&philo->arg->mutex_reverse);
	routine_exec(philo);
}
