/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_even.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 17:52:59 by earnaud           #+#    #+#             */
/*   Updated: 2021/08/25 14:48:40 by earnaud          ###   ########.fr       */
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
		write_action(DIE, philo->id, philo->param, philo);
		printf("%d die at %lld because last meal was at %lld\n", (philo->id) + 1, time, philo->last_meal);
		philo->param->all_alive = 0;
		return (1);
	}
	return (0);
}

void philo_sleep(t_philosopher *philo, long long sleep, int eat) //sometimes it die without needing for 214 200 200
{
	//long long i;
	long long time;
	int need_die;

	//i = 0;
	need_die = 0;
	time = get_time(philo->param);
	//if (time == philo->param->time_to_die)
	//	time++;
	//printf("for philo %d, time =%lld, and sleep=%lld and time to die=%d\n", philo->id + 1, time, sleep, philo->param->time_to_die);
	if ((time - philo->last_meal) + sleep > philo->param->time_to_die || sleep >= philo->param->time_to_die) //it was time - philo->last_meal) + sleep > 
	{
		//printf("he will sleep for %lld minus %lld\n", time, sleep);
		if (sleep >= time)
			{
			//printf("%lld %d will only 1 sleep %lld\n", time, philo->id + 1, philo->param->time_to_die - time);
			usleep((philo->param->time_to_die - (time - philo->last_meal)) * 1000);
			need_die = 1;
			}		
		else if (time < philo->param->time_to_die)
		{
			//printf("%lld %d will only 2 sleep %lld, timedie =%d\n", time, philo->id + 1, (philo->param->time_to_die - time), philo->param->time_to_die);
			//usleep(((time - sleep)) * 1000);
			usleep((philo->param->time_to_die - time) * 1000);
			need_die = 1;
		}
		else
		{
			//printf("%lld %d will only 3 sleep %lld\n", time, philo->id + 1, sleep);
			usleep (sleep * 1000);
		}
		if (need_die || sleep >= philo->param->time_to_die)
			{
				die(philo);
		//printf("and %d has die because time =%lld and timetodie%d and sleep%lld\n", philo->id + 1,time, philo->param->time_to_die, sleep);
			}
	}
	else
	{
		//printf("%d sleep normally and time is %lld\n", philo->id + 1, time);
		usleep(sleep * 1000);
	}
	if (eat)
		philo->last_meal = time;
	//printf("end of sleep\n");
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
	//printf("%d has taken the left fork %p\n",philo->id + 1, philo->fork_left);
	pthread_mutex_lock(philo->fork_left);
	if (!check_all_alive(philo->param, philo))
	{
		pthread_mutex_unlock(philo->fork_left);
		return ;
	}
	write_action(TAKE_FORK, philo->id, philo->param, philo);
	//printf("%d has taken the right fork %p\n",philo->id + 1, philo->fork_right);
	pthread_mutex_lock(philo->fork_right);
	if (!check_all_alive(philo->param, philo))
	{
	//	printf("eat even %d has die and release fork right and left\n", philo->id);
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return ;
	}
	write_action(TAKE_FORK, philo->id, philo->param, philo);
	write_action(EATING, philo->id, philo->param, philo);
	//philo->last_meal = get_time(philo->param);
	philo_sleep(philo, philo->param->time_to_eat, 1);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	//printf("%d is going to sleep\n", philo->id + 1);
	//printf("done sleeping\n");
}

void eat_odd(t_philosopher *philo)
{
	//printf("eat_odd with :%d\n", philo->id + 1);
	//printf("%d has taken the right fork %p\n",philo->id + 1, philo->fork_right);
	pthread_mutex_lock(philo->fork_right);
	if (!check_all_alive(philo->param, philo))
	{
		pthread_mutex_unlock(philo->fork_right);
		return ;
	}
	write_action(TAKE_FORK, philo->id, philo->param, philo);
	//printf("%d has taken the left fork %p\n",philo->id + 1, philo->fork_left);
	pthread_mutex_lock(philo->fork_left);
	if (!check_all_alive(philo->param, philo))
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		return ;
	}
	write_action(TAKE_FORK, philo->id, philo->param, philo);
	write_action(EATING, philo->id, philo->param, philo);
	philo->last_meal = get_time(philo->param);
	philo_sleep(philo, philo->param->time_to_eat, 1);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
	//printf("%d is going to sleep\n", philo->id + 1);
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
		write_action(SLEEPING, philo->id, philo->param, philo);
		philo_sleep(philo, philo->param->time_to_sleep, 0);
		philo->state = SLEEPING;
	}
	else if (philo->state == SLEEPING)
	{
		write_action(THINKING, philo->id, philo->param, philo);
		philo->state = THINKING;
	}
}