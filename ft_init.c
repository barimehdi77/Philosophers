/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 12:34:36 by mbari             #+#    #+#             */
/*   Updated: 2021/07/11 12:35:34 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_create_mutex(t_simulation *simulation)
{
	int i;

	i = 0;
	pthread_mutex_init(&simulation->message, NULL);
	pthread_mutex_init(&simulation->death, NULL);
	while (i < simulation->philo_numbers)
		pthread_mutex_init(simulation->forks + i++, NULL);
}

void	ft_destroy_all(t_simulation *simulation, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&simulation->death);
	pthread_mutex_destroy(&simulation->message);
	while (i < simulation->philo_numbers)
		pthread_mutex_destroy(simulation->forks + i++);
	free(philo);
	free(simulation->forks);
	free(simulation->threads);
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

void	ft_for_each_philo(t_simulation *simulation, t_philo *philo, int i)
{
	philo[i].index = i + 1;
	philo[i].left_hand = i;
	philo[i].right_hand = (i + 1) % simulation->philo_numbers;
	philo[i].is_dead = NO;
	philo[i].data = simulation;
	if (simulation->eat_counter == -1)
		philo[i].eat_counter = -1;
	else
		philo[i].eat_counter = simulation->eat_counter;
}

int	ft_error_put(char *messsage, int ret)
{
	printf("%s\n", messsage);
	return (ret);
}
