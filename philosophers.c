/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:11:11 by mbari             #+#    #+#             */
/*   Updated: 2021/07/01 17:42:28 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_error_put(char *messsage, int ret)
{
	printf("%s\n", messsage);
	return(ret);
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
			simulation->philo_numbers = num;
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
	return (0);
}

int main(int ac, char **av)
{
	int i;
	t_simulation	simulation;

	i = 1;
	printf("|%d|\n", ac);
		// return (0);
	if (ac == 5 || ac == 6)
	{
		while (av[i])
		{
			printf("|%d ==> %s|\n", i, av[i]);
			i++;
		}
		if (ft_parsing(av, &simulation))
			return (1);
		printf("|*************************|\n");
		printf("|1 : %d|2 : %d|3 : %d|4 : %d|5 : %d|\n", 
				simulation.philo_numbers, simulation.time_to_die, 
				simulation.time_to_eat, simulation.time_to_sleep, 
				simulation.notepme);
	}
	return (0);
}
