/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 11:52:58 by earnaud           #+#    #+#             */
/*   Updated: 2021/07/30 16:47:39 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long ft_atoi(const char *str)
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

void *osef()
{
	int i;
	i = 0;
}

int	thread_create(pthread_t *philo, int nbr)
{
	int i;

	i = 0;
	while (i < nbr)
	{
		if (pthread_create(philo + i++, NULL, &osef, NULL))
			return (1);
	}
	return (0);
}

int fork_create_assign(t_philosopher *philo, int nbr)
{
	int i;
	int j;
	pthread_mutex_t *forks;

	forks = malloc(sizeof(pthread_mutex_t) * nbr);
	if (!fork)
		return (1);
	i = 0;
	j = nbr - 1;
	while (i < nbr)
	{
		philo[i].state = THINKING;
		philo[i].fork_right = forks + i;
		philo[i].fork_left = forks + j;
		if (j == i)
			j = i - 1;
		else
			j++;
		i++;
	}
	return (0);
}

int set_param(t_philosopher *philo, char **argv)
{
	int i;
	t_param *param;

	param = malloc(sizeof(t_param));
	if (!param)
		return (1);
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
}

int main(int argc, char **argv)
{
	t_philosopher philo[4];

	set_param(philo, argv);
	if (fork_create_assign(philo, 4))
		return (1);
	if (thread_create(philo, 4))
		return (1);
	
	return (0);
}