/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:40:45 by gmersch           #+#    #+#             */
/*   Updated: 2024/05/06 17:06:27 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
#define PHILO_H

#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_arg
{
	int		time_start;
	int		nb_philo;
	int		time_eat;
	int		time_death;
	int		time_sleep;
	bool	is_nb_eat;
	int		nb_eat;
	int		is_someone_died;
	pthread_mutex_t	*mutex_s_died;
	pthread_mutex_t	*mutex_printf;

}	t_arg;

typedef struct s_philo
{
	int				id;
	bool			fork;
	pthread_mutex_t	*mutex_fork;
	int				time_last_eat;
	int				time_eating;
	int				time_sleep;
	int				nb_eat_time;

	struct s_philo	*next;

}	t_philo;

int		ft_atoi(const char *nptr);
void	define_arg(t_arg *arg, int argc, char **argv);
t_philo	*define_philo(t_arg *arg);
void	free_lst(t_philo *list);
void	free_lst_and_exit(t_philo *list);
void	free_philo(t_philo *list, t_arg *arg);
void	free_linked_lst(t_philo *list, t_arg *arg);



#endif
