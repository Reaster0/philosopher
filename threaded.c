/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threaded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 18:39:57 by earnaud           #+#    #+#             */
/*   Updated: 2021/08/03 16:50:09 by earnaud          ###   ########.fr       */
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
	return (0);
}

void *sleeping(t_philosopher *philo)
{
	write_action(SLEEPING, philo->id);
	usleep(philo->param->time_to_eat);
	return (0);
}

void *thinking(t_philosopher *philo)
{
	write_action(THINKING, philo->id);
	usleep(philo->param->time_to_sleep);
	return (0);
}

void *die(t_philosopher *philo)
{
	write_action(DIE, philo->id);
	philo->state = DIE;
	philo->param->all_alive = 0;
	// pthread_detach(philo->thread);
	return (0);
}

void *routine(void *arg)
{
	struct timeval time;
	t_philosopher *philo;

	philo = (t_philosopher *)arg;
	while (philo->param->all_alive)
	{
		gettimeofday(&time, NULL);
		if (philo->last_meal && (time.tv_usec - philo->last_meal) > philo->param->time_to_die)
		{
			die(philo);
			printf("%d die at %d because last meal was at %d\n", (philo->id) + 1, time.tv_usec, philo->last_meal);
			break;
		}
		else if (philo->param->nbr_philo % 2)
			algorythm_odd(philo);
		else
			algorythm_even(philo);
	}
	return (0);
}