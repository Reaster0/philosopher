/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_odd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 17:54:41 by earnaud           #+#    #+#             */
/*   Updated: 2021/09/01 17:59:52 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// void	eat_odd_wait(t_philosopher *philo)
// {
// 	odd_late_fork(philo);
// 	pthread_mutex_lock(philo->fork_right);
// 	if (!check_all_alive(philo->param, philo))
// 	{
// 		pthread_mutex_unlock(philo->fork_right);
// 		return ;
// 	}
// 	write_action(TAKE_FORK, philo->id, philo->param, philo);
// 	ft_sleep(1);
// 	odd_late_fork(philo);
// 	pthread_mutex_lock(philo->fork_left);
// 	if (!check_all_alive(philo->param, philo))
// 	{
// 		pthread_mutex_unlock(philo->fork_right);
// 		pthread_mutex_unlock(philo->fork_left);
// 		return ;
// 	}
// 	write_action(TAKE_FORK, philo->id, philo->param, philo);
// 	write_action(EATING, philo->id, philo->param, philo);
// 	philo_sleep(philo, philo->param->time_to_eat, 1);
// 	pthread_mutex_unlock(philo->fork_right);
// 	pthread_mutex_unlock(philo->fork_left);
// }

// void	algorythm_odd(t_philosopher *philo)
// {
// 	if (philo->state == THINKING)
// 	{
// 		if ((philo->id + 1) % 2 && philo->param->nbr_philo != 1)
// 			eat_odd_wait(philo);
// 		else
// 			eat_even(philo);
// 		philo->state = EATING;
// 	}
// 	else if (philo->state == EATING)
// 	{
// 		write_action(SLEEPING, philo->id, philo->param, philo);
// 		philo_sleep(philo, philo->param->time_to_sleep, 0);
// 		philo->state = SLEEPING;
// 	}
// 	else if (philo->state == SLEEPING)
// 	{
// 		write_action(THINKING, philo->id, philo->param, philo);
// 		philo->state = THINKING;
// 	}
// }
