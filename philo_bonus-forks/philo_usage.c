/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 18:37:59 by earnaud           #+#    #+#             */
/*   Updated: 2021/08/31 19:35:15 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	thread_create(t_philosopher *philo, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr)
	{
		if (pthread_create(&(philo + i)->thread, NULL, &routine, philo + i))
			return (1);
		i++;
	}
	return (0);
}

int	set_mutex(t_param *param)
{
	param->alive_mutex = malloc(sizeof(pthread_mutex_t));
	if (!param->alive_mutex)
		return (1);
	if (pthread_mutex_init(param->alive_mutex, NULL))
		return (1);
	return (0);
}

int	create_philo(t_philosopher **philo, t_param *param)
{
	int	i;

	if (set_mutex(param))
		return (1);
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

int	set_philo(t_philosopher **philo, char **argv)
{
	t_param	*param;

	param = malloc(sizeof(t_param));
	if (!param)
		return (1);
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
	if (create_philo(philo, param))
		return (1);
	return (0);
}

void	write_action(t_state state, int id_philo,
			t_param *param, t_philosopher *philo)
{
	long long	time;

	time = get_time(param);
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
		printf("%lld %d has die\n", time, id_philo + 1);
}
