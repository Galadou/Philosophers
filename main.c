#include "philo.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_arg	*arg;
	t_philo	*philo;
	t_philo *buffer;

	if (argc < 5 || argc >  6)
		exit (1);
	define_arg(&arg, argc, argv);
	philo = define_philo(&arg);
	buffer = philo;
	while (philo)
	{
		printf("%d = id, %d = time to eat, %d = time to sleep, %d = fourchette\n", philo->id, philo->time_eating, philo->time_sleep, philo->fork);
		philo = philo->next;
	}
	philo = buffer;
	//while (il y a des philo)
	//je lanceles thread avec les routines
	pthread_mutex_destroy(arg->mutex_printf);
	pthread_mutex_destroy(arg->mutex_s_died);
	free(arg->mutex_printf);
	free(arg->mutex_s_died);
	free_philo(philo, arg);
}
