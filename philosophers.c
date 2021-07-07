/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:11:11 by mbari             #+#    #+#             */
/*   Updated: 2021/07/07 15:07:39 by mbari            ###   ########.fr       */
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
			simulation->threads = malloc(sizeof(pthread_t) * num);
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

void	ft_for_each_philo(t_simulation *simulation, t_philo *philo, int i)
{
	philo[i].index = i + 1;
	philo[i].left_hand = i;
	philo[i].right_hand = (i + 1) % simulation->philo_numbers;
	philo[i].is_dead = NO;
	if (simulation->eat_counter == -1)
		philo[i].eat_counter = -1;
	else
		philo[i].eat_counter = simulation->eat_counter;
}

t_philo	*ft_philo_init(t_simulation *simulation)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_philo) * simulation->philo_numbers);
	while (++i < simulation->philo_numbers)
		ft_for_each_philo(simulation, philo, i);
	return (philo);
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
		while (i < simulation.philo_numbers)
		{
			simulation.philo_index = i;
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
	}
	return (0);
}
