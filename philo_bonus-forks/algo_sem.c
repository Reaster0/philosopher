/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_sem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 18:30:54 by earnaud           #+#    #+#             */
/*   Updated: 2021/09/14 18:22:26 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	eat_one(t_philosopher *philo)
{
	check_all_alive(philo);
	write_action(TAKE_FORK, philo->id, philo->param, philo);
	ft_sleep(philo->param->time_to_die);
	die(philo);
}

void	even_late_fork(t_philosopher *philo)
{
	if (philo->param->time_to_die < philo->param->time_to_eat * 2
		+ philo->param->time_to_sleep || philo->param->time_to_die
		< philo->param->time_to_sleep * 2 + philo->param->time_to_die)
	{
		write_action(TAKE_FORK, philo->id, philo->param, philo);
		sem_wait(philo->forks);
		write_action(TAKE_FORK, philo->id, philo->param, philo);
		sem_wait(philo->forks);
		write_action(EATING, philo->id, philo->param, philo);
		ft_sleep(philo->param->time_to_eat);
		sem_post(philo->forks);
		sem_post(philo->forks);
		write_action(SLEEPING, philo->id, philo->param, philo);
		ft_sleep(philo->param->time_to_die - (get_time(philo->param)
				- philo->last_meal));
		die(philo);
	}
}

void	eat_sem(t_philosopher *philo)
{
	if ((philo->id + 1) % 2)
		odd_late_fork(philo);
	if (!((philo->id + 1) % 2) && philo->param->nbr_philo % 2)
		even_late_fork(philo);
	sem_wait(philo->forks);
	check_all_alive(philo);
	write_action(TAKE_FORK, philo->id, philo->param, philo);
	sem_wait(philo->forks);
	check_all_alive(philo);
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
		if (philo->param->nbr_philo == 1)
		{
			eat_one(philo);
			return ;
		}
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
