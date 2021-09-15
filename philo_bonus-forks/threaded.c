/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threaded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 18:39:57 by earnaud           #+#    #+#             */
/*   Updated: 2021/09/15 12:18:18 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*die(t_philosopher *philo)
{
	check_all_alive(philo);
	sem_wait(philo->param->sem_alive);
	write_action(DIE, philo->id, philo->param, philo);
	exit (0);
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

	sem_wait(philo->param->starting_block);
	sem_post(philo->param->starting_block);
	if ((philo->id + 1) % 2 && philo->param->time_to_die
		> philo->param->time_to_eat + philo->param->time_to_sleep
		&& philo->param->nbr_philo != 1)
		ft_sleep(philo->param->time_to_eat);
	while (check_all_alive(philo))
	{
		time = get_time(philo->param);
		if ((time - philo->last_meal) >= philo->param->time_to_die)
		{
			die(philo);
			exit (0);
		}
		else
		{
			algorythm_sem(philo);
		}
	}
	exit (0);
}

void	kill_all(int *id_list, int nbr, int *all_alive, t_philosopher *philo)
{
	int	i;

	if (!all_alive)
		return ;
	i = 0;
	all_alive = 0;
	sem_close(philo->forks);
	sem_close(philo->param->sem_alive);
	sem_close(philo->param->writing);
	sem_close(philo->param->starting_block);
	while (i < nbr)
	{
		kill(id_list[i], SIGTERM);
		i++;
	}
}

void	*pre_routine(void *arg)
{
	t_philosopher	*philo;
	t_param			param_stack;
	t_philosopher	philo_stack;

	philo = (t_philosopher *)arg;
	philo->param->id_list[philo->id] = fork();
	if (!philo->param->id_list[philo->id])
	{
		copy_param_stack(philo->param, &param_stack);
		copy_philo_stack(philo, &philo_stack, &param_stack);
		free(philo->param->id_list);
		free(philo->param);
		if (!philo->id)
			free(philo);
		routine(&philo_stack);
	}
	waitpid(0, NULL, WUNTRACED);
	kill_all(philo->param->id_list, philo->param->nbr_philo,
		&(philo->param->all_alive), philo);
	return (0);
}
