/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:11:38 by mbari             #+#    #+#             */
/*   Updated: 2021/07/05 19:19:23 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_philo
{
	int	index;
	int	right_hand;
	int	left_hand;
	int	notepme;
}				t_philo;

typedef struct s_simulation
{
	pthread_t	*threads;
	int			philo_numbers;
	int			forks;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			notepme;
}				t_simulation;

#endif
