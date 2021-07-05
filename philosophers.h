/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:11:38 by mbari             #+#    #+#             */
/*   Updated: 2021/07/05 20:18:10 by mbari            ###   ########.fr       */
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

typedef struct s_philo
{
	int	index;
	int	right_hand;
	int	left_hand;
	int	is_dead;
	int	eat_counter;
}				t_philo;

typedef struct s_simulation
{
	pthread_t	*threads;
	//t_philo		*philo;
	int			philo_index;
	int			philo_numbers;
	int			forks;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			eat_counter;
}				t_simulation;

#endif
