/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:11:11 by mbari             #+#    #+#             */
/*   Updated: 2021/07/16 11:18:37 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_check_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->next_meal < ft_get_time())
		{
			philo->data->is_dead = YES;
			pthread_mutex_lock(philo->eat);
			ft_print_message(DIED, philo);
			pthread_mutex_unlock(philo->data->stop);
			break ;
		}
	}
	return (NULL);
}

int	ft_check_eat(t_philo *philo)
{
	if ((philo->data->eat_counter != -1)
		&& (philo->data->current_eat >= philo->data->max_eat))
	{
		philo->data->is_dead = YES;
		pthread_mutex_lock(philo->eat);
		ft_print_message(DONE, philo);
		pthread_mutex_unlock(philo->data->stop);
		return (0);
	}
	return (1);
}

void	*ft_routine(void *arg)
{
	t_philo		*philo;
	pthread_t	death;

	philo = arg;
	philo->next_meal = ft_get_time() + (unsigned int)philo->data->time_to_die;
	pthread_create(&death, NULL, ft_check_death, philo);
	pthread_detach(death);
	while (1)
	{
		if (philo->data->is_dead)
			break ;
		ft_take_fork(philo);
		ft_eat(philo);
		if (!ft_check_eat(philo))
			break ;
		ft_sleep(philo);
		ft_print_message(THINKING, philo);
	}
	return (NULL);
}

int	ft_error_put(t_simulation *simulation, char *message, int ret)
{
	if (simulation)
	{
		if (simulation->threads)
			free(simulation->threads);
		if (simulation->forks)
			free(simulation->forks);
	}
	printf("%s\n", message);
	return (ret);
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
			return (0);
		philo = ft_philo_init(&simulation);
		simulation.start = ft_get_time();
		ft_create_mutex(&simulation);
		pthread_mutex_lock(simulation.stop);
		while (i < simulation.philo_numbers)
		{
			pthread_create(simulation.threads + i, NULL, ft_routine, philo + i);
			pthread_detach(simulation.threads[i++]);
			usleep(100);
		}
		pthread_mutex_lock(simulation.stop);
		ft_destroy_all(&simulation, philo);
	}
	else
		printf("Error: Too many arguments\n");
	return (0);
}
