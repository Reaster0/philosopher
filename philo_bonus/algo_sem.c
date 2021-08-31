/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_sem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 18:30:54 by earnaud           #+#    #+#             */
/*   Updated: 2021/08/31 19:35:30 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	eat_sem(t_philosopher *philo)
{
	sem_wait(philo->forks);
	if (!check_all_alive(philo->param, philo))
	{
		sem_post(philo->forks);
		return ;
	}
	write_action(TAKE_FORK, philo->id, philo->param, philo);
	sem_wait(philo->forks);
	if (!check_all_alive(philo->param, philo))
	{
		sem_post(philo->forks);
		sem_post(philo->forks);
		return ;
	}
	write_action(TAKE_FORK, philo->id, philo->param, philo);
	write_action(EATING, philo->id, philo->param, philo);
	philo_sleep(philo, philo->param->time_to_eat, 1);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	algorythm_sem(t_philosopher *philo)
{
		if (philo->state == THINKING)
	{
	// 	if ((philo->id + 1) % 2)
	// 		eat_odd(philo);
	// 	else
			eat_sem(philo);
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