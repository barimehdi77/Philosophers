/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:11:38 by mbari             #+#    #+#             */
/*   Updated: 2021/07/11 12:36:49 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# define YES 1
# define NO 0
typedef struct s_simulation
{
	pthread_t			*threads;
	pthread_mutex_t		*forks;
	pthread_mutex_t		message;
	pthread_mutex_t		death;
	int					philo_numbers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					eat_counter;
}				t_simulation;

typedef struct s_philo
{
	t_simulation	*data;
	int				index;
	int				right_hand;
	int				left_hand;
	int				is_dead;
	int				eat_counter;
}				t_philo;

void	ft_create_mutex(t_simulation *simulation);
void	ft_destroy_all(t_simulation *simulation, t_philo *philo);
t_philo	*ft_philo_init(t_simulation *simulation);
void	ft_for_each_philo(t_simulation *simulation, t_philo *philo, int i);
int		ft_error_put(char *messsage, int ret);

#endif
