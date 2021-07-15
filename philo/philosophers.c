/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:11:11 by mbari             #+#    #+#             */
/*   Updated: 2021/07/15 19:11:34 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_check_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philo->data->death);
		if (philo->next_meal < ft_get_time())
		{
			ft_print_message(DIED, philo);
			pthread_mutex_unlock(philo->data->stop);
			break ;
		}
		pthread_mutex_unlock(philo->data->death);
		pthread_mutex_lock(philo->data->death);
		if ((philo->data->eat_counter != -1)
			&& (philo->data->current_eat >= philo->data->max_eat))
		{
			ft_print_message(DONE, philo);
			pthread_mutex_unlock(philo->data->stop);
			break ;
		}
		pthread_mutex_unlock(philo->data->death);
	}
	return (NULL);
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
		ft_take_fork(philo);
		ft_eat(philo);
		ft_sleep(philo);
		ft_print_message(THINKING, philo);
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
		if (ft_parsing(av, &simulation))
			return (1);
		philo = ft_philo_init(&simulation);
		simulation.start = ft_get_time();
		ft_create_mutex(&simulation);
		pthread_mutex_lock(simulation.stop);
		while (i < simulation.philo_numbers)
		{
			pthread_create(simulation.threads + i, NULL, ft_routine, philo + i);
			pthread_detach(simulation.threads[i]);
			i++;
		}
		pthread_mutex_lock(simulation.stop);
		ft_destroy_all(&simulation, philo);
	}
	return (0);
}
