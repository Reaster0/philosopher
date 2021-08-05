/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threaded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 18:39:57 by earnaud           #+#    #+#             */
/*   Updated: 2021/08/05 17:59:18 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void *die(t_philosopher *philo)
{
	pthread_mutex_lock(philo->param->alive_mutex);
	if (!philo->param->all_alive)
		return (0);
	philo->param->all_alive = 0;
	pthread_mutex_unlock(philo->param->alive_mutex);
	write_action(DIE, philo->id, philo->param);
	//printf("%d die at %lld because last meal was at %lld, the difference is %lld\n", (philo->id) + 1, get_time(philo->param), philo->last_meal, get_time(philo->param) - philo->last_meal);
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
			break;
		}
		else if (philo->param->nbr_philo % 2)
			algorythm_odd(philo);
		else
			algorythm_even(philo);
	}
	return (0);
}