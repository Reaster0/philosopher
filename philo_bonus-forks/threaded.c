/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threaded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 18:39:57 by earnaud           #+#    #+#             */
/*   Updated: 2021/09/01 18:19:16 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*die(t_philosopher *philo)
{
	check_all_alive(philo);
	sem_wait(philo->param->sem_alive);
	//pthread_mutex_lock(philo->param->alive_mutex);
	//if (!philo->param->all_alive)
	//{
	//	pthread_mutex_unlock(philo->param->alive_mutex);
	//	return (0);
	//}
	//philo->param->all_alive = 0;
	//pthread_mutex_unlock(philo->param->alive_mutex);
	write_action(DIE, philo->id, philo->param, philo);
	exit (0);
	//return (0);
}

int	check_all_alive(t_philosopher *philo)
{
	sem_wait(philo->param->sem_alive);
	sem_post(philo->param->sem_alive);
	if (!philo->nbr_eat)
	{
		sem_wait(philo->param->sem_alive);
		exit (0);
	}
	return (1);
}

void	*routine(t_philosopher *philo)
{
	long long		time;

	while (check_all_alive(philo))
	{
		time = get_time(philo->param);
		if ((time - philo->last_meal) > philo->param->time_to_die)
		{
			die(philo);
			exit (0);
		}
		// else if (philo->param->nbr_philo % 2)
		// 	algorythm_odd(philo);
		else
			algorythm_sem(philo);
	}
	return (0);
}
