#include "philo.h"

void	routine(t_philo *philo, t_arg *arg)
{
	//je crois aue y'q pqs besoins du if, pour qil qttende juste que le mutex des deuxx soit libre pour manger
	if (philo->id % 2 == 1 && philo->fork == true && philo->next->fork == true) // si impaire et mange pas et fouchette libre
	{
		pthread_mutex_lock(philo->mutex_fork);
		pthread_mutex_lock(philo->next->mutex_fork);
		philo->fork = false;
		philo->next->fork = false;
		pthread_mutex_lock(arg->mutex_printf);
		printf("{%d} | %s is eating\n", arg->time_start, philo->id);
		pthread_mutex_unlock(arg->mutex_printf);
		//si le temps pour manger est trop long et qu'il va mourir
		//j'attend pile le temps ou il va mourir puis mort
		//A FAIRE CE QUIL Y A MARQUE SI DESSUS
		usleep(arg->time_eat);//pas secure
		philo->time_last_eat = gettimeofday(NULL, NULL);
		philo->fork = true;
		philo->next->fork = true;
		pthread_mutex_unlock(philo->mutex_fork); //junlock tard psk personne va toucher au fouchtte si elle sont pas la donc je delock que quand dispo
		pthread_mutex_unlock(philo->next->mutex_fork);
	}
//



}
