/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:11:11 by mbari             #+#    #+#             */
/*   Updated: 2021/07/04 18:49:03 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_error_put(char *messsage, int ret)
{
	printf("%s\n", messsage);
	return (ret);
}

int	ft_parsing(char **av, t_simulation *simulation)
{
	int				num;
	int				i;
	int				j;

	i = 1;
	j = 0;
	while (av[i])
	{
		j = 0;
		num = 0;
		while (av[i][j])
		{
			if (av[i][j] >= '0' && av[i][j] <= '9')
				 num = num * 10 + (av[i][j] - '0');
			else
				return (ft_error_put("Error: Number Only", 1));
			j++;
		}
		if (i == 1)
		{
			simulation->philo_numbers = num;
			simulation->forks = num;
			simulation->threads = (pthread_t *)malloc(sizeof(pthread_t) * num);
		}
		else if (i == 2)
			simulation->time_to_die = num;
		else if (i == 3)
			simulation->time_to_eat = num;
		else if (i == 4)
			simulation->time_to_sleep = num;
		else if (i == 5)
			simulation->notepme = num;
		i++;
	}
	if (i == 5)
		simulation->notepme = -1;
	return (0);
}

int	main(int ac, char **av)
{
	int				i;
	t_simulation	simulation;

	i = 1;
	if (ac == 5 || ac == 6)
	{
		if (ft_parsing(av, &simulation))
			return (1);
	}
	return (0);
}
