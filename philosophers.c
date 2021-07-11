/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:11:11 by mbari             #+#    #+#             */
/*   Updated: 2021/07/11 14:11:19 by mbari            ###   ########.fr       */
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
			simulation->time_to_die = num * 1000;
		else if (i == 3)
			simulation->time_to_eat = num * 1000;
		else if (i == 4)
			simulation->time_to_sleep = num * 1000;
		else if (i == 5)
			simulation->eat_counter = num;
		i++;
	}
	if (i == 5)
		simulation->eat_counter = -1;
	return (0);
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
	ft_print_message(EATING, philo);
	philo->eat_counter++;
	usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->left_hand]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_hand]);
}

void	ft_think(t_philo *philo)
{
	int time_to_think;

	time_to_think = philo->data->time_to_die
		- philo->data->time_to_sleep - philo->data->time_to_eat;
	ft_print_message(THINKING, philo);
	usleep(time_to_think);
}

void	ft_sleep(t_philo *philo)
{
	ft_print_message(SLEEPING, philo);
	usleep(philo->data->time_to_sleep);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	// printf("thread number %d has started\n", philo->index + 1);
	// sleep(1);
	// printf("thread number %d has ended\n", philo->index + 1);
	while (1)
	{
		ft_take_fork(philo);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

unsigned int	ft_get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
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
			usleep(100);
			i++;
		}
		pthread_mutex_lock(simulation.stop);
		ft_destroy_all(&simulation, philo);
	}
	return (0);
}
