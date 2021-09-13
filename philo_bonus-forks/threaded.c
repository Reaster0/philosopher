/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threaded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 18:39:57 by earnaud           #+#    #+#             */
/*   Updated: 2021/09/13 15:30:40 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	copy_philo_stack(t_philosopher *src, t_philosopher *dst, t_param *param)
{
	dst->forks = src->forks;
	dst->id = src->id;
	dst->last_meal = src->last_meal;
	dst->nbr_eat = src->nbr_eat;
	dst->param = param; 
	dst->state = src->state;
	dst->thread = src->thread;
}

void copy_param_stack(t_param *src, t_param *dst)
{
	dst->all_alive = src->all_alive;
	dst->nbr_philo = src->nbr_philo;
	dst->nbr_philo_eat = src->nbr_philo_eat;
	dst->sem_alive = src->sem_alive;
	dst->starting_block = src->starting_block;
	dst->time_start = src->time_start;
	dst->time_to_die = src->time_to_die;
	dst->time_to_eat = src->time_to_eat;
	dst->time_to_sleep = src->time_to_sleep;
	dst->writing = src->writing;
	dst->id_list = 0;
}

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

	sem_wait(philo->param->starting_block);
	sem_post(philo->param->starting_block);
	if (philo->id > philo->param->nbr_philo / 2)
		ft_sleep(1);
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

void kill_all(int *id_list, int nbr, int *all_alive, t_philosopher *philo)
{
	int i;

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
	wait(NULL);
	kill_all(philo->param->id_list, philo->param->nbr_philo, &(philo->param->all_alive), philo);
	return (0);
}