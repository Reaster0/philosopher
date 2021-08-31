/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threaded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 18:39:57 by earnaud           #+#    #+#             */
/*   Updated: 2021/08/31 13:58:46 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*die(t_philosopher *philo)
{
	pthread_mutex_lock(philo->param->alive_mutex);
	if (!philo->param->all_alive)
	{
		pthread_mutex_unlock(philo->param->alive_mutex);
		return (0);
	}
	philo->param->all_alive = 0;
	pthread_mutex_unlock(philo->param->alive_mutex);
	write_action(DIE, philo->id, philo->param, philo);
	return (0);
}

int	check_all_alive(t_param *param, t_philosopher *philo)
{
	int	result;

	result = 0;
	pthread_mutex_lock(param->alive_mutex);
	if (param->all_alive)
		result = 1;
	pthread_mutex_unlock(param->alive_mutex);
	if (!philo->nbr_eat)
	{
		pthread_mutex_lock(param->alive_mutex);
		param->all_alive = 0;
		pthread_mutex_unlock(param->alive_mutex);
		result = 0;
	}
	return (result);
}

void	*routine(void *arg)
{
	long long		time;
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (check_all_alive(philo->param, philo))
	{
		time = get_time(philo->param);
		if ((time - philo->last_meal) > philo->param->time_to_die)
		{
			die(philo);
			break ;
		}
		else if (philo->param->nbr_philo % 2)
			algorythm_odd(philo);
		else
			algorythm_even(philo);
	}
	return (0);
}
