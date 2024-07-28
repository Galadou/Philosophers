/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:35:50 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/28 11:43:29 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static int	ft_check_arg(char **argv, int y)
{
	int	x;

	if (!ft_strlen(argv[y]))
	{
		printf("Error : Empty arg detected\n");
		return (1);
	}
	if (ft_atoi(argv[y]) > 2147483647 || ft_atoi(argv[y]) < -2147483647)
	{
		printf("Error : An arg is bigger or lower than expected (int)\n");
		return (1);
	}
	x = 0;
	while (argv[y][x])
	{
		if (!ft_isdigit(argv[y][x]))
		{
			printf("Error : A non-numeric arg is detected\n");
			return (1);
		}
		x++;
	}
	return (0);
}

int	ft_parsing(int argc, char **argv)
{
	int	y;

	if (argc < 5 || argc > 6)
	{
		printf("Error : Too many or too much arg\n");
		return (1);
	}
	y = 1;
	while (argv[y])
	{
		if (ft_check_arg(argv, y))
			return (1);
		y++;
	}
	return (0);
}
