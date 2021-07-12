/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 12:28:24 by mbari             #+#    #+#             */
/*   Updated: 2021/07/12 12:28:34 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_set_rest(t_simulation *simulation, int num, int i)
{
	if (i == 4)
	{
		if (num < 60)
			return (printf("THE time_to_sleep CAN'T BE LESS THAN 60 ms\n"));
		simulation->time_to_sleep = num;
	}
	else if (i == 5)
	{
		if (num == 0)
			simulation->eat_counter = -1;
		else
		{
			simulation->eat_counter = num;
			simulation->current_eat = 0;
			simulation->max_eat = num * simulation->philo_numbers;
		}
	}
}

void	ft_set_data(t_simulation *simulation, int num, int i)
{
	if (i == 1)
	{
		if (num == 0)
			return (printf("NO PHELOSOPHER IN THE TABILE\n"));
		simulation->philo_numbers = num;
		simulation->threads = malloc(sizeof(pthread_t) * num);
		simulation->forks = malloc(sizeof(pthread_mutex_t) * num);
	}
	else if (i == 2)
	{
		if (num < 60)
			return (printf("THE time_to_die CAN'T BE LESS THAN 60 ms\n"));
		simulation->time_to_die = num;
	}
	else if (i == 3)
	{
		if (num < 60)
			return (printf("THE time_to_eat CAN'T BE LESS THAN 60 ms\n"));
		simulation->time_to_eat = num;
	}
	else
		ft_set_rest(simulation, num, i);
}

int	ft_get_number(char *arg)
{
	int	i;
	int	num;

	i = 0;
	while (arg[i])
	{
		if (arg[i] >= '0' && arg[i] <= '9')
			num = num * 10 + (arg[i] - '0');
		else
			return (printf("Error: Number Only"));
		i++;
	}
	return (num);
}

int	ft_parsing(char **av, t_simulation *simulation)
{
	int				num;
	int				i;

	i = 1;
	while (av[i])
	{
		num = ft_get_number(av[i]);
		ft_set_data(simulation, num, i);
		i++;
	}
	if (i == 5)
	{
		simulation->eat_counter = -1;
		simulation->current_eat = -1;
		simulation->max_eat = -1;
	}
	return (0);
}
