/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 12:34:36 by mbari             #+#    #+#             */
/*   Updated: 2021/07/16 11:20:19 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_create_mutex(t_simulation *simulation)
{
	int	i;

	i = 0;
	pthread_mutex_init(simulation->message, NULL);
	pthread_mutex_init(simulation->death, NULL);
	pthread_mutex_init(simulation->stop, NULL);
	while (i < simulation->philo_numbers)
		pthread_mutex_init(simulation->forks + i++, NULL);
}

void	ft_destroy_all(t_simulation *simulation, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(simulation->death);
	pthread_mutex_destroy(simulation->message);
	pthread_mutex_destroy(simulation->stop);
	while (i < simulation->philo_numbers)
	{
		pthread_mutex_destroy(simulation->forks + i);
		pthread_mutex_destroy(philo[i].eat);
		free(philo[i].eat);
		i++;
	}
	free(philo);
	free(simulation->forks);
	free(simulation->threads);
	free(simulation->death);
	free(simulation->message);
	free(simulation->stop);
}

t_philo	*ft_philo_init(t_simulation *simulation)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_philo) * simulation->philo_numbers);
	simulation->stop = malloc(sizeof(pthread_mutex_t));
	simulation->death = malloc(sizeof(pthread_mutex_t));
	simulation->message = malloc(sizeof(pthread_mutex_t));
	while (++i < simulation->philo_numbers)
		ft_for_each_philo(simulation, philo, i);
	return (philo);
}

void	ft_for_each_philo(t_simulation *simulation, t_philo *philo, int i)
{
	philo[i].index = i;
	philo[i].left_hand = i;
	philo[i].right_hand = (i + 1) % simulation->philo_numbers;
	philo[i].is_dead = NO;
	philo[i].data = simulation;
	philo[i].eat = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo[i].eat, NULL);
	if (simulation->eat_counter == -1)
		philo[i].eat_counter = -1;
	else
		philo[i].eat_counter = simulation->eat_counter;
}

void	ft_print_message(int id, t_philo *philo)
{
	unsigned int	time;

	pthread_mutex_lock(philo->data->message);
	time = ft_get_time() - philo->data->start;
	if (id == FORK)
		printf("%u\t%d has taken a fork\n", time, philo->index + 1);
	else if (id == EATING)
		printf("%u\t%d is eating\n", time, philo->index + 1);
	else if (id == SLEEPING)
		printf("%u\t%d is sleeping\n", time, philo->index + 1);
	else if (id == THINKING)
		printf("%u\t%d is thinking\n", time, philo->index + 1);
	else if (id == DIED)
		printf("%u\t%d died\n", time, philo->index + 1);
	else if (id == DONE)
		printf("Simulation is Done :)\n");
	if (id != DIED && id != DONE)
		pthread_mutex_unlock(philo->data->message);
}
