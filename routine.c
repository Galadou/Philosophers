#include "philo.h"

static long	abso(long c)
{
	if (c < 0)
		return (c * -1);
	return (c);
}

static void	routine_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)//si philo paire alors je prend dabord ma fourchette et inverse si je suis impaire
	{
		pthread_mutex_lock(philo->mutex_fork);
		pthread_mutex_lock(philo->next->mutex_fork);
	}
	else
	{
		pthread_mutex_lock(philo->next->mutex_fork);
		pthread_mutex_lock(philo->mutex_fork);
	}
	philo->fork = false;
	philo->next->fork = false;
	pthread_mutex_lock(philo->arg->mutex_printf);
	gettimeofday(&philo->time_now, NULL);
	printf("{%ld} | %d is eating\n", ((abso((philo->arg->time_start.tv_usec / 1000) - (philo->time_now.tv_usec / 1000))) + abso((philo->arg->time_start.tv_sec * 1000) - (philo->time_now.tv_sec * 1000))), philo->id);
	pthread_mutex_unlock(philo->arg->mutex_printf);
	usleep(philo->arg->time_eat * 1000);
	gettimeofday(&philo->time_last_eat, NULL);
	philo->fork = true;
	philo->next->fork = true;
	pthread_mutex_unlock(philo->mutex_fork); //junlock tard psk personne va toucher au fouchtte si elle sont pas la donc je delock que quand dispo
	pthread_mutex_unlock(philo->next->mutex_fork);
}

static void	routine_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->arg->mutex_printf);
	gettimeofday(&philo->time_now, NULL);
	printf("{%ld} | %d is sleeping\n", ((abso((philo->arg->time_start.tv_usec / 1000) - (philo->time_now.tv_usec / 1000))) + abso((philo->arg->time_start.tv_sec * 1000) - (philo->time_now.tv_sec * 1000))), philo->id);
	pthread_mutex_unlock(philo->arg->mutex_printf);
	usleep(philo->arg->time_sleep * 1000);//pas secure si mort
}

static void	routine_think(t_philo *philo)
{
	pthread_mutex_lock(philo->arg->mutex_printf);
	gettimeofday(&philo->time_now, NULL);
	printf("{%ld} | %d is thinking\n", ((abso((philo->arg->time_start.tv_usec / 1000) - (philo->time_now.tv_usec / 1000))) + abso((philo->arg->time_start.tv_sec * 1000) - (philo->time_now.tv_sec * 1000))), philo->id);
	pthread_mutex_unlock(philo->arg->mutex_printf);
}

void	*routine_main(void *pt)
{
	bool	can_eat;
	t_philo *philo;

	philo = (t_philo *)pt;
	if (philo->id % 2 == 0)
		can_eat =  false;
	else
		can_eat = true;
	while (philo->arg->is_someone_died == false)
	{
		if (can_eat == true)
			routine_eat(philo);
		if (can_eat == false)
			can_eat = true;
		routine_sleep(philo);
		routine_think(philo);
	}
	return (0);
}
