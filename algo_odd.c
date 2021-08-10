/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_odd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 17:54:41 by earnaud           #+#    #+#             */
/*   Updated: 2021/08/09 15:27:47 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void eat_odd_wait(t_philosopher *philo)
{
	pthread_mutex_lock(philo->fork_right);
	write_action(TAKE_FORK, philo->id, philo->param);
	usleep(1000);
	pthread_mutex_lock(philo->fork_left);
	write_action(TAKE_FORK, philo->id, philo->param);
	write_action(EATING, philo->id, philo->param);
	philo->last_meal = get_time(philo->param);
	philo_sleep(philo, philo->param->time_to_eat);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
}

void algorythm_odd(t_philosopher *philo)
{
		if (philo->state == THINKING)
	{
		if ((philo->id + 1) % 2)
			eat_odd_wait(philo);
		else
			eat_even(philo);
		philo->state = EATING;
	}
	else if (philo->state == EATING)
	{
		write_action(SLEEPING, philo->id, philo->param);
		philo_sleep(philo, philo->param->time_to_sleep);
		philo->state = SLEEPING;
	}
	else if (philo->state == SLEEPING)
	{
		write_action(THINKING, philo->id, philo->param);
		philo->state = THINKING;
	}
}