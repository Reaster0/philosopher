/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 11:53:12 by earnaud           #+#    #+#             */
/*   Updated: 2021/07/30 16:38:14 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef enum e_state
{
	EATING,
	THINKING,
	SLEEPING
}			t_state;

typedef struct s_param
{
	int nbr_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int nbr_philo_eat;

}				t_param;

typedef struct s_philosopher
{
	pthread_t		thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_state			state;
	t_param			*param;

}				t_philosopher