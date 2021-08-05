/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threaded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 18:39:57 by earnaud           #+#    #+#             */
/*   Updated: 2021/08/05 14:07:56 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void *eating(t_philosopher *philo)
{
	pthread_mutex_lock(philo->fork_right);
	write_action(TAKE_FORK, philo->id, philo->param);
	pthread_mutex_lock(philo->fork_left);
	write_action(TAKE_FORK, philo->id, philo->param);
	write_action(EATING, philo->id, philo->param);
	usleep(philo->param->time_to_eat);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (0);
}

void *sleeping(t_philosopher *philo)
{
	write_action(SLEEPING, philo->id, philo->param);
	usleep(philo->param->time_to_eat);
	return (0);
}

void *thinking(t_philosopher *philo)
{
	write_action(THINKING, philo->id, philo->param);
	usleep(philo->param->time_to_sleep);
	return (0);
}

void *die(t_philosopher *philo)
{
	philo->param->all_alive = 0;
	write_action(DIE, philo->id, philo->param);
	return (0);
}

void *routine(void *arg)
{
	long long time;
	t_philosopher *philo;

	philo = (t_philosopher *)arg;
	while (philo->param->all_alive)
	{
		time = get_time(philo->param);
		if (philo->last_meal && (time - philo->last_meal) > philo->param->time_to_die)
		{
			die(philo);
			printf("%d die at %lld because last meal was at %lld\n", (philo->id) + 1, time, philo->last_meal);
			break;
		}
		else if (philo->param->nbr_philo % 2)
			algorythm_odd(philo);
		else
			algorythm_even(philo);
	}
	return (0);
}