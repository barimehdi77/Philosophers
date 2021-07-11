/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:11:11 by mbari             #+#    #+#             */
/*   Updated: 2021/07/11 17:11:33 by mbari            ###   ########.fr       */
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
				return (printf("Error: Number Only"));
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

void	*ft_check_death(void *arg)
{
	t_philo	*philo;
	int		count;

	philo = (t_philo *)arg;
	count = 1;
	while (count)
	{
		if (philo->eat_counter != -1)
			count = philo->eat_counter;
		// printf("counter : %d\n", count);
		if (philo->data->limit < ft_get_time())
		{
			ft_print_message(DIED, philo);
			pthread_mutex_unlock(philo->data->stop);
		}
		// printf("count : %d\n", count);
		// if (count == 0)
		// {
		// 	ft_print_message(DONE, philo);
		// 	pthread_mutex_unlock(philo->data->stop);
		// }
	}
	ft_print_message(DONE, philo);
	pthread_mutex_unlock(philo->data->stop);
	return (NULL);
}

void	*ft_routine(void *arg)
{
	t_philo		*philo;
	pthread_t	death;

	philo = arg;
	philo->data->limit = ft_get_time() + (unsigned int)philo->data->time_to_die;
	pthread_create(&death, NULL, ft_check_death, philo);
	pthread_detach(death);
	// printf("counter : %d\n", philo->eat_counter);
	while (1)
	{
		ft_take_fork(philo);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
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
		simulation.start = ft_get_time();
		if (ft_parsing(av, &simulation))
			return (1);
		philo = ft_philo_init(&simulation);
		ft_create_mutex(&simulation);
		pthread_mutex_lock(simulation.stop);
		while (i < simulation.philo_numbers)
		{
			pthread_create(simulation.threads + i, NULL, ft_routine, philo + i);
			pthread_detach(simulation.threads[i]);
			usleep(1000);
			i++;
		}
		pthread_mutex_lock(simulation.stop);
		ft_destroy_all(&simulation, philo);
	}
	return (0);
}
