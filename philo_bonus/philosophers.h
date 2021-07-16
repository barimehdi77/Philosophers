/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:11:38 by mbari             #+#    #+#             */
/*   Updated: 2021/07/16 09:05:26 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <semaphore.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>

# define YES 1
# define NO 0
# define FORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DIED 5
# define DONE 6

typedef struct s_simulation
{
	sem_t			*forks;
	sem_t			*message;
	sem_t			*death;
	sem_t			*stop;
	unsigned int	start;
	int				philo_numbers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_counter;
	int				max_eat;
	int				current_eat;
}				t_simulation;

typedef struct s_philo
{
	t_simulation	*data;
	pid_t			pid;
	unsigned int	eating_time;
	unsigned int	next_meal;
	int				index;
	int				is_dead;
	int				eat_counter;
}				t_philo;

unsigned int	ft_get_time(void);
void			ft_routine(t_philo *philo);
void			ft_eat(t_philo *philo);
void			ft_sleep(t_philo *philo);
int				ft_get_number(char *arg);
void			*ft_check_death(void *arg);
void			ft_take_fork(t_philo *philo);
void			ft_print_message(int id, t_philo *philo);
t_philo			*ft_philo_init(t_simulation *simulation);
void			ft_create_semaphores(t_simulation *simulation);
int				ft_parsing(char **av, t_simulation *simulation);
int				ft_set_rest(t_simulation *simulation, int num, int i);
int				ft_set_data(t_simulation *simulation, int num, int i);
void			ft_destroy_all(t_simulation *simulation, t_philo *philo);
void			ft_for_each_philo(t_simulation *simulation, t_philo *philo,
					int i);
int				ft_error_put(t_simulation *simulation, char *message, int ret);

#endif
