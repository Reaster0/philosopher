/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 17:56:17 by earnaud           #+#    #+#             */
/*   Updated: 2021/09/01 15:04:37 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	time_to_sleep(t_philosopher *philo, long long sleep, long long time)
{
	int	need_die;

	need_die = 0;
	if (sleep >= time)
	{
			//		printf("%d will sleep for %lld\n", philo->id, philo->param->time_to_die - (time - philo->last_meal));
		ft_sleep(philo->param->time_to_die - (time - philo->last_meal));
		need_die = 1;
	}
	else if (time < philo->param->time_to_die)
	{
			//		printf("%d will sleep for %lld\n", philo->id, philo->param->time_to_die - time);
		ft_sleep(philo->param->time_to_die - time);
		need_die = 1;
	}
	else
		ft_sleep(sleep);
	if (need_die || sleep >= philo->param->time_to_die)
		die(philo);
}

void	philo_sleep(t_philosopher *philo, long long sleep, int eat)
{
	long long	time;

	time = get_time(philo->param);
	if (eat)
		philo->last_meal = time;
	if ((time - philo->last_meal) + sleep > philo->param->time_to_die
		|| sleep >= philo->param->time_to_die)
		time_to_sleep(philo, sleep, time);
	else
	{
		//	printf("%d will sleep for %lld\n", philo->id, sleep);
		ft_sleep(sleep);
	}
}

long long	get_time_portable(long long time_start)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - time_start);
}

void	ft_sleep(long milliseconds)
{
	long long	time_start;

	if (milliseconds < 0)
		milliseconds *= -1;
	time_start = get_time_portable(0);
	while (get_time_portable(time_start) < milliseconds)
	{
		usleep(100);
	}
}
