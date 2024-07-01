/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_phio_dead.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:44:42 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/01 17:55:10 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	am_i_dead(t_philo *philo)
{
	gettimeofday(&philo->time_now, NULL);
	if (philo->time_now.tv_usec - philo->time_last_eat.tv_usec > philo->arg->time_death * 1000)
		//return ?? or kill everyone ???
}
