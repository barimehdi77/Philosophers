/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:11:11 by mbari             #+#    #+#             */
/*   Updated: 2021/07/11 12:37:16 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
			simulation->threads = malloc(sizeof(pthread_t) * num);
			simulation->forks = malloc(sizeof(pthread_mutex_t) * num);
		}
		else if (i == 2)
			simulation->time_to_die = num;
		else if (i == 3)
			simulation->time_to_eat = num;
		else if (i == 4)
			simulation->time_to_sleep = num;
		else if (i == 5)
			simulation->eat_counter = num;
		i++;
	}
	if (i == 5)
		simulation->eat_counter = -1;
	return (0);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	printf("thread number %d has started\n", philo->index);
	sleep(1);
	printf("thread number %d has ended\n", philo->index);
	return (NULL);
}

int	main(int ac, char **av)
{
	int				i;
	t_simulation	simulation;
	t_philo			*philo;

	i = 0;
	if (ac == 5 || ac == 6)
	{
		if (ft_parsing(av, &simulation))
			return (1);
		philo = ft_philo_init(&simulation);
		ft_create_mutex(&simulation);
		while (i < simulation.philo_numbers)
		{
			pthread_create(simulation.threads + i, NULL,
				ft_routine, philo + i);
			i++;
		}
		i = 0;
		while (i < simulation.philo_numbers)
		{
			pthread_join(simulation.threads[i], NULL);
			i++;
		}
		ft_destroy_all(&simulation, philo);
	}
	return (0);
}
