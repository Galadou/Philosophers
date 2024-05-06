#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int	nb;
	int	negatif;

	nb = 0;
	negatif = 1;
	while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
		nptr++;
	while (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			negatif = -1;
		nb++;
		nptr++;
	}
	if (nb >= 2)
		return (0);
	nb = 0;
	while (ft_isdigit(*nptr))
	{
		nb = nb * 10 + (*nptr - 48);
		nptr++;
	}
	return (nb * negatif);
}
