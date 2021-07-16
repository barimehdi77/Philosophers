/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 12:28:24 by mbari             #+#    #+#             */
/*   Updated: 2021/07/16 09:06:23 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_set_rest(t_simulation *simulation, int num, int i)
{
	if (i == 4)
	{
		if (num < 60)
			return (ft_error_put(simulation,
					"Error: THE time_to_sleep CAN'T BE LESS THAN 60 ms", 1));
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
	return (0);
}

int	ft_error_put(t_simulation *simulation, char *message, int ret)
{
	if (simulation)
	{
		if (simulation->forks)
			free(simulation->forks);
	}
	printf("%s\n", message);
	return (ret);
}

int	ft_set_data(t_simulation *simulation, int num, int i)
{
	if (i == 1)
	{
		if (num == 0)
			return (ft_error_put(NULL,
					"Error: NO PHELOSOPHER IN THE TABILE", 1));
		simulation->philo_numbers = num;
	}
	else if (i == 2)
	{
		if (num < 60)
			return (ft_error_put(simulation,
					"Error: THE time_to_die CAN'T BE LESS THAN 60 ms", 1));
		simulation->time_to_die = num;
	}
	else if (i == 3)
	{
		if (num < 60)
			return (ft_error_put(simulation,
					"Error: THE time_to_eat CAN'T BE LESS THAN 60 ms", 1));
		simulation->time_to_eat = num;
	}
	else
		ft_set_rest(simulation, num, i);
	return (0);
}

int	ft_get_number(char *arg)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (arg[i])
	{
		if (arg[i] >= '0' && arg[i] <= '9')
			num = num * 10 + (arg[i] - '0');
		else
			return (ft_error_put(NULL, "Error: Number Only", -1));
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
		if (num == -1)
			return (1);
		if (ft_set_data(simulation, num, i))
			return (1);
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
