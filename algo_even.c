/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_even.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 17:52:59 by earnaud           #+#    #+#             */
/*   Updated: 2021/08/05 14:07:57 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int check_if_will_die(t_philosopher *philo, int usleep)
{
	long long time;

	if (!philo->param->all_alive)
		return (1);
	time = get_time(philo->param);
	if (philo->last_meal && (time - philo->last_meal) + usleep > philo->param->time_to_die)
	{
		write_action(DIE, philo->id, philo->param);
		printf("%d die at %lld because last meal was at %lld\n", (philo->id) + 1, time, philo->last_meal);
		philo->param->all_alive = 0;
		return (1);
	}
	return (0);
}

void eat_even(t_philosopher *philo)
{	
	pthread_mutex_lock(philo->fork_left);
	if (check_if_will_die(philo, philo->param->time_to_eat))
		return ;
	write_action(TAKE_FORK, philo->id, philo->param);
	pthread_mutex_lock(philo->fork_right);
	if (check_if_will_die(philo, philo->param->time_to_eat))
		return ;
	write_action(TAKE_FORK, philo->id, philo->param);
	write_action(EATING, philo->id, philo->param);
	usleep(philo->param->time_to_eat);
	philo->last_meal = get_time(philo->param);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void eat_odd(t_philosopher *philo)
{
	pthread_mutex_lock(philo->fork_right);
	if (check_if_will_die(philo, philo->param->time_to_eat))
		return ;
	write_action(TAKE_FORK, philo->id, philo->param);
	pthread_mutex_lock(philo->fork_left);
	if (check_if_will_die(philo, philo->param->time_to_eat))
		return ;
	write_action(TAKE_FORK, philo->id, philo->param);
	write_action(EATING, philo->id, philo->param);
	usleep(philo->param->time_to_eat);
	philo->last_meal = get_time(philo->param);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
}

void algorythm_even(t_philosopher *philo)
{
	if (philo->state == THINKING)
	{
		if ((philo->id + 1) % 2)
			eat_odd(philo);
		else
			eat_even(philo);
		philo->state = EATING;
	}
	else if (philo->state == EATING)
	{
		if (check_if_will_die(philo, philo->param->time_to_sleep))
			return ;
		write_action(SLEEPING, philo->id, philo->param);
		usleep(philo->param->time_to_sleep);
		philo->state = SLEEPING;
	}
	else if (philo->state == SLEEPING)
	{
		write_action(THINKING, philo->id, philo->param);
		philo->state = THINKING;
	}
}