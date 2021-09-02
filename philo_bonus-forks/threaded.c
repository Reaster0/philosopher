/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threaded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 18:39:57 by earnaud           #+#    #+#             */
/*   Updated: 2021/09/02 15:11:48 by earnaud          ###   ########.fr       */
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
	sem_wait(philo->param->writing);
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
	
	//philo->param->time_start = get_time(philo->param);
	sem_wait(philo->param->starting_block);
	sem_post(philo->param->starting_block);

	//usleep(100);
	while (check_all_alive(philo))
	{
		time = get_time(philo->param);
		if ((time - philo->last_meal) > philo->param->time_to_die)
		{
			die(philo);
			exit (0);
		}
		else
			algorythm_sem(philo);
	}
	exit (0);
}
