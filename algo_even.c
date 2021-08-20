/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_even.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 17:52:59 by earnaud           #+#    #+#             */
/*   Updated: 2021/08/18 16:49:15 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int check_if_will_die(t_philosopher *philo, int sleep)
{
	long long time;

	if (!philo->param->all_alive)
		return (1);
	time = get_time(philo->param);
	if (philo->last_meal && (time - philo->last_meal) + sleep > philo->param->time_to_die)
	{
		write_action(DIE, philo->id, philo->param);
		printf("%d die at %lld because last meal was at %lld\n", (philo->id) + 1, time, philo->last_meal);
		philo->param->all_alive = 0;
		return (1);
	}
	return (0);
}

void philo_sleep(t_philosopher *philo, long long sleep)
{
	long long i;
	long long time;

	i = 0;
	if ((get_time(philo->param) - philo->last_meal) + sleep > philo->param->time_to_die)
	{
		//printf("%lld %d will only sleep %lld\n", get_time(philo->param), philo->id, time - sleep);
		usleep(((get_time(philo->param) - sleep) - 7) * 1000);
		die(philo);
	}
	else
		usleep(sleep * 1000);
}

int check_if_dead(t_param *param)
{
	pthread_mutex_lock(param->alive_mutex);
	if (!param->all_alive)
		return (1);
	pthread_mutex_unlock(param->alive_mutex);
	return (0);
}

void eat_even(t_philosopher *philo)
{
	pthread_mutex_lock(philo->fork_left);
	if (!check_all_alive(philo->param))
		return ;
	write_action(TAKE_FORK, philo->id, philo->param);
	pthread_mutex_lock(philo->fork_right);
	if (!check_all_alive(philo->param))
		return ;
	write_action(TAKE_FORK, philo->id, philo->param);
	write_action(EATING, philo->id, philo->param);
	philo->last_meal = get_time(philo->param);
	philo_sleep(philo, philo->param->time_to_eat);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void eat_odd(t_philosopher *philo)
{
	pthread_mutex_lock(philo->fork_right);
	if (!check_all_alive(philo->param))
		return ;
	write_action(TAKE_FORK, philo->id, philo->param);
	pthread_mutex_lock(philo->fork_left);
	if (!check_all_alive(philo->param))
		return ;
	write_action(TAKE_FORK, philo->id, philo->param);
	write_action(EATING, philo->id, philo->param);
	philo->last_meal = get_time(philo->param);
	philo_sleep(philo, philo->param->time_to_eat);
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