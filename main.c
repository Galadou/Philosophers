#include "philo.h"

int	main(int argc, char **argv)
{
	t_arg	*arg;
	t_philo	*philo;
	t_philo *buffer;

	if (argc < 5 || argc >  6)
		exit (1); //interdit exit
	arg = define_arg(argc, argv);
	philo = define_philo(arg);
	buffer = philo;
	// int i = 0;
	// while (i != 5)
	// {
	// 	printf("%d = id, %d = time to eat, %d = time to sleep, %d = fourchette\n", philo->id, philo->time_eating, philo->time_sleep, philo->fork);
	// 	philo = philo->next;
	// 	i++;
	// }
	//philo = buffer;
	while (philo)
	{
		pthread_create(&(philo->thread), NULL, routine_main, philo);
		philo = philo->next;
		//printf("BOUCLE\n");
		if (philo == buffer)
			break;
	}
	philo = buffer;
	while (philo->id < arg->nb_philo)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		if (philo == buffer)
			break;
	}
	philo = buffer;//besoins ?
	pthread_mutex_destroy(arg->mutex_printf);
	pthread_mutex_destroy(arg->mutex_s_died);
	free(arg->mutex_printf);
	free(arg->mutex_s_died);
	free_philo(philo, arg);
	free(arg);
}

//nb philo
//t_die
//t_eat
//t_sleep
//nb philo eat
