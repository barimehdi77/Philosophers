/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:11:11 by mbari             #+#    #+#             */
/*   Updated: 2021/07/16 09:02:15 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_check_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->death);
		if (philo->next_meal < ft_get_time())
		{
			ft_print_message(DIED, philo);
			sem_post(philo->data->stop);
			break ;
		}
		sem_post(philo->data->death);
		sem_wait(philo->data->death);
		if ((philo->data->eat_counter != -1)
			&& (philo->data->current_eat >= philo->data->max_eat))
		{
			ft_print_message(DONE, philo);
			sem_post(philo->data->stop);
			break ;
		}
		sem_post(philo->data->death);
	}
	return (NULL);
}

void	ft_routine(t_philo *philo)
{
	pthread_t	death;

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
}

void	ft_create_process(t_simulation *simulation, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < simulation->philo_numbers)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			ft_routine(philo + i);
			exit(0);
		}
		i++;
		usleep(100);
	}
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
		ft_create_semaphores(&simulation);
		sem_wait(simulation.stop);
		ft_create_process(&simulation, philo);
		sem_wait(simulation.stop);
		ft_destroy_all(&simulation, philo);
	}
	else
		printf("Error: Too many arguments\n");
	return (0);
}
