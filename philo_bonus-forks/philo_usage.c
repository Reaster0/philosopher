/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 18:37:59 by earnaud           #+#    #+#             */
/*   Updated: 2021/09/14 14:34:40 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	thread_create(t_philosopher *philo, int nbr)
{
	int	i;

	i = 0;
	sem_wait(philo->param->starting_block);
	philo->param->time_start = get_time(philo->param);
	while (i < nbr)
	{
		if (pthread_create(&(philo + i)->thread, NULL, &pre_routine,
				(philo + i)))
			return (1);
		i++;
	}
	sem_post(philo->param->starting_block);
	return (0);
}

int	create_philo(t_philosopher **philo, t_param *param)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philosopher) * param->nbr_philo);
	if (!*philo)
		return (1);
	while (i < param->nbr_philo)
	{
		(*philo)[i].nbr_eat = param->nbr_philo_eat;
		(*philo)[i].id = i;
		(*philo)[i++].param = param;
	}
	(*philo)[0].param->all_alive = 1;
	return (0);
}

int	set_param(t_param *param, char **argv)
{
	argv++;
	param->time_start = 0;
	param->nbr_philo = ft_atoi(*argv);
	argv++;
	param->time_to_die = ft_atoi(*argv);
	argv++;
	param->time_to_eat = ft_atoi(*argv);
	argv++;
	param->time_to_sleep = ft_atoi(*argv);
	argv++;
	if (*argv)
		param->nbr_philo_eat = ft_atoi(*argv);
	else
		param->nbr_philo_eat = -1;
	param->id_list = malloc(sizeof(int) * param->nbr_philo);
	if (!param->id_list)
		return (1);
	return (0);
}

int	set_philo(t_philosopher **philo, char **argv)
{
	t_param	*param;

	param = malloc(sizeof(t_param));
	if (!param)
		return (1);
	if (set_param(param, argv))
		return (1);
	param->writing = sem_open("writing", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("writing");
	param->sem_alive = sem_open("all_alive", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("all_alive");
	param->starting_block = sem_open("starting", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("starting");
	if (create_philo(philo, param))
		return (1);
	return (0);
}

void	write_action(t_state state, int id_philo,
			t_param *param, t_philosopher *philo)
{
	long long	time;

	time = get_time(param);
	sem_wait(param->writing);
	if (state == EATING)
	{
		printf("%lld %d is eating\n", time, id_philo + 1);
		philo->nbr_eat--;
	}
	else if (state == THINKING)
		printf("%lld %d is thinking\n", time, id_philo + 1);
	else if (state == SLEEPING)
		printf("%lld %d is sleeping\n", time, id_philo + 1);
	else if (state == TAKE_FORK)
		printf("%lld %d has taken a fork\n", time, id_philo + 1);
	else if (state == DIE)
		printf("%lld %d died\n", time, id_philo + 1);
	if (state != DIE)
		sem_post(param->writing);
}
