/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:40:45 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/28 17:44:36 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_arg
{
	struct timeval	time_start;
	int				nb_philo;
	int				time_eat;
	int				time_death;
	int				time_sleep;
	bool			is_nb_eat;
	int				nb_eat;
	int				nb_finish_eat;
	int				is_someone_died;
	pthread_mutex_t	mutex_finish_eat;
	pthread_mutex_t	mutex_s_died;
	pthread_mutex_t	mutex_printf;

}	t_arg;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	pthread_mutex_t	mutex_l_fork;
	pthread_mutex_t	*mutex_r_fork;
	struct timeval	time_last_eat;
	struct timeval	time_start_eat;
	struct timeval	time_start_sleep;
	struct timeval	time_now;
	int				time_eating;
	int				time_sleep;
	int				nb_eat;

	t_arg			*arg;
	struct s_philo	*next;

}	t_philo;

int			ft_parsing(int argc, char **argv);
long int	ft_atoi(const char *nptr);
t_arg		*define_arg(int argc, char **argv);
t_philo		*define_philo(t_arg *arg);
void		*free_lst(t_philo *list);
void		free_philo(t_philo *list, t_arg *arg);
void		free_linked_lst(t_philo *list, t_arg *arg);
int			free_arg(t_arg *arg);

void		*routine_main(void *philo);
void		routine_eat(t_philo *philo);
bool		ft_am_i_dead(t_philo *philo);
int			ft_check_dead(t_philo *philo, bool l, bool r);

#endif
