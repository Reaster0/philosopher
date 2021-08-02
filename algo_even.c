/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_even.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 17:52:59 by earnaud           #+#    #+#             */
/*   Updated: 2021/08/02 18:53:55 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void eat_even(t_philosopher *philo)
{
	struct timeval time;

	pthread_mutex_lock(philo->fork_left);
	write_action(TAKE_FORK, philo->id);
	pthread_mutex_lock(philo->fork_right);
	write_action(TAKE_FORK, philo->id);
	write_action(EATING, philo->id);
	usleep(philo->param->time_to_eat);
	gettimeofday(&time, NULL);
	philo->last_meal = time.tv_usec;
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void eat_odd(t_philosopher *philo)
{
	struct timeval time;

	pthread_mutex_lock(philo->fork_right);
	write_action(TAKE_FORK, philo->id);
	pthread_mutex_lock(philo->fork_left);
	write_action(TAKE_FORK, philo->id);
	write_action(EATING, philo->id);
	usleep(philo->param->time_to_eat);
	gettimeofday(&time, NULL);
	philo->last_meal = time.tv_usec;
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
}

void algorythm_even(t_philosopher *philo)
{
	if (philo->state == THINKING)
	{
		if (philo->id % 2)
			eat_odd(philo);
		else
			eat_even(philo);
		philo->state = EATING;
	}
	else if (philo->state == EATING)
	{
		write_action(SLEEPING, philo->id);
		usleep(philo->param->time_to_sleep);
		philo->state = SLEEPING;
	}
	else if (philo->state == SLEEPING)
	{
		write_action(THINKING, philo->id);
		philo->state = THINKING;
	}
}