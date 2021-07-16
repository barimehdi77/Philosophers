/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 16:47:03 by mbari             #+#    #+#             */
/*   Updated: 2021/07/16 10:02:48 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	ft_get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	ft_take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_hand]);
	ft_print_message(FORK, philo);
	pthread_mutex_lock(&philo->data->forks[philo->right_hand]);
	ft_print_message(FORK, philo);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->eat);
	ft_print_message(EATING, philo);
	if (philo->data->eat_counter != -1)
		philo->data->current_eat++;
	philo->eating_time = ft_get_time();
	philo->next_meal = philo->eating_time
		+ (unsigned int)philo->data->time_to_die;
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[philo->left_hand]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_hand]);
	pthread_mutex_unlock(philo->eat);
}

void	ft_sleep(t_philo *philo)
{
	usleep(10);
	ft_print_message(SLEEPING, philo);
	usleep(philo->data->time_to_sleep * 1000);
}
