/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threaded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 18:39:57 by earnaud           #+#    #+#             */
/*   Updated: 2021/07/30 20:57:20 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void *eating(t_philosopher *philo)
{
	pthread_mutex_lock(philo->fork_right);
	write_action(TAKE_FORK, philo->id);
	pthread_mutex_lock(philo->fork_left);
	write_action(TAKE_FORK, philo->id);
	write_action(EATING, philo->id);
	usleep(philo->param->time_to_eat);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void *sleeping(t_philosopher *philo)
{
	write_action(SLEEPING, philo->id);
	usleep(philo->param->time_to_eat);
}

void *thinking(t_philosopher *philo)
{
	write_action(THINKING, philo->id);
	usleep(philo->param->time_to_sleep);
}

void *die(t_philosopher *philo)
{
	write_action(DIE, philo->id);
	philo->state = DIE;
	pthread_detach(philo->thread);
}

void *routine(t_philosopher *philo)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	if (philo->last_meal && (time.tv_usec - philo->last_meal) > philo->param->time_to_die)
		die(philo);
	else
		eating(philo);
}