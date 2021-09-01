/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 18:37:59 by earnaud           #+#    #+#             */
/*   Updated: 2021/09/01 18:44:21 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// int	thread_create(t_philosopher *philo, int nbr)
// {
// 	int	i;

// 	i = 0;
// 	while (i < nbr)
// 	{
// 		if (pthread_create(&(philo + i)->thread, NULL, &routine, philo + i))
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

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
	sem_unlink("writing");
	param->writing = sem_open("writing", O_CREAT, S_IRWXU, 1);
	sem_unlink("all_alive");
	param->sem_alive = sem_open("all_alive", O_CREAT, S_IRWXU, 1);
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
		printf("%lld %d has die\n", time, id_philo + 1);
	sem_post(param->writing);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(long long n)
{
	long long nb;

	nb = n;
	if (n < 0)
	{
		write(1, "-", 1);
		nb = -nb;
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putchar((nb % 10) + '0');
	}
	else
		ft_putchar(nb + '0');
}

void	ft_putstr(char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		write(1, &s[i++], 1);
}

// void	write_action(t_state state, int id_philo,
// 			t_param *param, t_philosopher *philo)
// {
// 	long long	time;

// 	time = get_time(param);
// 	if (state == EATING)
// 	{
// 		ft_putnbr(time);
// 		ft_putchar(' ');
// 		ft_putnbr(id_philo + 1);
// 		ft_putstr(" is eating\n");
// 		philo->nbr_eat--;
// 	}
// 	else if (state == THINKING)
// 	{
// 		ft_putnbr(time);
// 		ft_putchar(' ');
// 		ft_putnbr(id_philo + 1);
// 		ft_putstr(" is thinking\n");
// 	}
// 	else if (state == SLEEPING)
// 	{
// 		ft_putnbr(time);
// 		ft_putchar(' ');
// 		ft_putnbr(id_philo + 1);
// 		ft_putstr(" is sleeping\n");
// 	}
// 	else if (state == TAKE_FORK)
// 	{
// 		ft_putnbr(time);
// 		ft_putchar(' ');
// 		ft_putnbr(id_philo + 1);
// 		ft_putstr(" has taken a fork\n");
// 	}
// 	else if (state == DIE)
// 	{
// 		ft_putnbr(time);
// 		ft_putchar(' ');
// 		ft_putnbr(id_philo + 1);
// 		ft_putstr(" has die\n");
// 	}
// }
