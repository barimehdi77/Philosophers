/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:11:38 by mbari             #+#    #+#             */
/*   Updated: 2021/07/01 17:33:45 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <string.h>

typedef	struct	s_philo
{
	int	index;
	int	right_hand;
	int	left_hand;
	int	notepme;
}				t_philo;

typedef	struct	s_simulation
{
	int	philo_numbers;
	int	forks;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	notepme;
}				t_simulation;

#endif
