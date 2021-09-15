/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 18:45:08 by earnaud           #+#    #+#             */
/*   Updated: 2021/09/14 18:22:14 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	ft_atoi(const char *str)
{
	int		i;
	long	nbr;
	int		neg;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	neg = (str[i] == '-') * -2 + 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	nbr = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr * neg);
}

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

void	copy_param_stack(t_param *src, t_param *dst)
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

void	odd_late_fork2(t_philosopher *philo)
{
	if (philo->param->time_to_eat * 2 > philo->param->time_to_die)
	{
		write_action(TAKE_FORK, philo->id, philo->param, philo);
		sem_wait(philo->forks);
		write_action(TAKE_FORK, philo->id, philo->param, philo);
		sem_wait(philo->forks);
		write_action(EATING, philo->id, philo->param, philo);
		ft_sleep(philo->param->time_to_die - (get_time(philo->param)));
		die(philo);
	}
	if (philo->param->time_to_sleep * 2 > philo->param->time_to_die)
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
		ft_sleep(philo->param->time_to_die - (get_time(philo->param)));
		die(philo);
	}
}

void	odd_late_fork(t_philosopher *philo)
{
	if (philo->param->nbr_philo != 1 && philo->param->nbr_philo % 2
		&& (get_time(philo->param) - philo->last_meal)
		+ philo->param->time_to_eat >= philo->param->time_to_die
		&& (philo->param->time_to_eat * 2)
		+ philo->param->time_to_sleep >= philo->param->time_to_die)
	{
		ft_sleep(philo->param->time_to_die
			- (get_time(philo->param) - philo->last_meal));
		die(philo);
	}
	odd_late_fork2(philo);
}
