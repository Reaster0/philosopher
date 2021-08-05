/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_even.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 17:52:59 by earnaud           #+#    #+#             */
/*   Updated: 2021/08/04 13:59:40 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int check_if_will_die(t_philosopher *philo, int usleep)
{
	struct timeval time;

	if (!philo->param->all_alive)
		return (1);
	gettimeofday(&time, NULL);
	if (philo->last_meal && (time.tv_usec - philo->last_meal) + usleep > philo->param->time_to_die)
	{
		write_action(DIE, philo->id);
		printf("%d die at %d because last meal was at %d\n", (philo->id) + 1, time.tv_usec, philo->last_meal);
		philo->param->all_alive = 0;
		return (1);
	}
	return (0);
}

void eat_even(t_philosopher *philo)
{
	struct timeval time;
	
	pthread_mutex_lock(philo->fork_left);
	if (check_if_will_die(philo, philo->param->time_to_eat))
		return ;
	write_action(TAKE_FORK, philo->id);
	pthread_mutex_lock(philo->fork_right);
	if (check_if_will_die(philo, philo->param->time_to_eat))
		return ;
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
	if (check_if_will_die(philo, philo->param->time_to_eat))
		return ;
	write_action(TAKE_FORK, philo->id);
	pthread_mutex_lock(philo->fork_left);
	if (check_if_will_die(philo, philo->param->time_to_eat))
		return ;
	write_action(TAKE_FORK, philo->id);
	write_action(EATING, philo->id);
	gettimeofday(&time, NULL);
	usleep(philo->param->time_to_eat);
	philo->last_meal = time.tv_usec;
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