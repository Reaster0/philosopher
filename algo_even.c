/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_even.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 17:52:59 by earnaud           #+#    #+#             */
/*   Updated: 2021/08/20 19:07:33 by earnaud          ###   ########.fr       */
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
	time = get_time(philo->param);
	if ((time - philo->last_meal) + sleep > philo->param->time_to_die)
	{
		//printf("%lld %d will only sleep %lld\n", time, philo->id, time - sleep);
		//printf("he will sleep for %lld minus %lld\n", time, sleep);
		if (sleep > time)
			usleep((philo->param->time_to_die - time) * 1000); // maybe sleep -7
		else
			usleep(((time - sleep)) * 1000); //maybe sleep - 7
		die(philo);
		//printf("and has die\n");
	}
	else
	{
		//printf("%d sleep normally\n", philo->id);
		usleep(sleep * 1000);
	}
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
	//printf("eat_even with :%d\n", philo->id + 1);
	pthread_mutex_lock(philo->fork_left);
	if (!check_all_alive(philo->param))
	{
		pthread_mutex_unlock(philo->fork_right);
		return ;
	}	write_action(TAKE_FORK, philo->id, philo->param);
	pthread_mutex_lock(philo->fork_right);
	if (!check_all_alive(philo->param))
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		return ;
	}
	write_action(TAKE_FORK, philo->id, philo->param);
	write_action(EATING, philo->id, philo->param);
	philo->last_meal = get_time(philo->param);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	//printf("%d is going to sleep\n", philo->id + 1);
	philo_sleep(philo, philo->param->time_to_eat);
	//printf("done sleeping\n");
}

void eat_odd(t_philosopher *philo)
{
	//printf("eat_odd with :%d\n", philo->id + 1);
	pthread_mutex_lock(philo->fork_right);
	if (!check_all_alive(philo->param))
	{
		pthread_mutex_unlock(philo->fork_right);
		return ;
	}
	write_action(TAKE_FORK, philo->id, philo->param);
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