/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_odd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 17:54:41 by earnaud           #+#    #+#             */
/*   Updated: 2021/08/20 19:04:26 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void eat_odd_wait(t_philosopher *philo)
{
	//printf("eat_odd_wait with :%d\n", philo->id + 1);
	pthread_mutex_lock(philo->fork_right);
	if (!check_all_alive(philo->param))
	{
		pthread_mutex_unlock(philo->fork_right);
		return ;
	}
	write_action(TAKE_FORK, philo->id, philo->param);
	usleep(1000);
	pthread_mutex_lock(philo->fork_left);
	if (!check_all_alive(philo->param))
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		return ;
	}
	write_action(TAKE_FORK, philo->id, philo->param);
	write_action(EATING, philo->id, philo->param);
	philo->last_meal = get_time(philo->param);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
	//printf("%d is going to sleep\n", philo->id + 1);
	philo_sleep(philo, philo->param->time_to_eat);
	//printf("done sleeping\n");
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