/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 11:53:12 by earnaud           #+#    #+#             */
/*   Updated: 2021/09/02 14:58:46 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

typedef enum e_state
{
	EATING,
	THINKING,
	SLEEPING,
	TAKE_FORK,
	DIE
}			t_state;

typedef struct s_param
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_philo_eat;
	int				all_alive;
	sem_t			*writing;
	sem_t			*sem_alive;
	sem_t			*starting_block;
	pthread_mutex_t	*alive_mutex;
	long long		time_start;
}					t_param;

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	sem_t			*forks;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_state			state;
	t_param			*param;
	int				nbr_eat;
	long long		last_meal;
}					t_philosopher;

int			set_philo(t_philosopher **philo, char **argv);
int			create_philo(t_philosopher **philo, t_param *param);
int			fork_create_assign(t_philosopher *philo, int nbr);
int			thread_create(t_philosopher *philo, int nbr);
long		ft_atoi(const char *str);
void		write_action(t_state state, int id_philo,
				t_param *param, t_philosopher *philo);
void		*routine(t_philosopher *philo);
void		algorythm_even(t_philosopher *philo);
void		algorythm_odd(t_philosopher *philo);
long long	get_time(t_param *param);
void		*die(t_philosopher *philo);
void		eat_even(t_philosopher *philo);
void		eat_odd(t_philosopher *philo);
int			ft_check_error(int argc, char **argv);
void		philo_sleep(t_philosopher *philo, long long sleep, int eat);
int			check_all_alive(t_philosopher *philo);
void		ft_sleep(long nbr);
void		odd_late_fork(t_philosopher *philo);
int			fork_create_assign(t_philosopher *philo, int nbr);
void		algorythm_sem(t_philosopher *philo);
int			process_create(t_philosopher *philo);
void		setup_sem_launching(sem_t *starting, int nbr);

#endif