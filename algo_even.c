/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_even.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 17:52:59 by earnaud           #+#    #+#             */
/*   Updated: 2021/08/30 23:02:19 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	time_to_sleep(t_philosopher *philo, long long sleep, long long time)
{
	int	need_die;

	need_die = 0;
//	printf("%lld time to sleep\n", time);
	if (sleep >= time)
	{
		ft_sleep(philo->param->time_to_die - (time - philo->last_meal));
		need_die = 1;
	}
	else if (time < philo->param->time_to_die)
	{
		ft_sleep(philo->param->time_to_die - time);
		need_die = 1;
	}
	else
		ft_sleep(sleep);
	if (need_die || sleep >= philo->param->time_to_die)
		die(philo);
}

void	philo_sleep(t_philosopher *philo, long long sleep, int eat)
{
	long long	time;

	time = get_time(philo->param);
	if (eat)
		philo->last_meal = time;
	//printf("%lld philo %d sleep %lld and eat %d\n", time, philo->id + 1, sleep, eat);
	if ((time - philo->last_meal) + sleep > philo->param->time_to_die || sleep
		>= philo->param->time_to_die)
		time_to_sleep(philo, sleep, time);
	else
	{
		//printf("%lld ft_sleep\n", time);
		ft_sleep(sleep);
	}
}

void	eat_even(t_philosopher *philo)
{
	if (philo->param->nbr_philo % 2 && (get_time(philo->param) - philo->last_meal) + philo->param->time_to_eat > philo->param->time_to_die && (philo->param->time_to_eat * 2) + philo->param->time_to_sleep >= philo->param->time_to_die)
	{
	//	printf("fork too for %d time %lld last meal %lld time die %d\n",philo->id +1, get_time(philo->param), philo->last_meal, philo->param->time_to_die);
		ft_sleep(philo->param->time_to_die - (get_time(philo->param) - philo->last_meal));
		die(philo);
	}
	pthread_mutex_lock(philo->fork_left);
	if (!check_all_alive(philo->param, philo))
	{
		pthread_mutex_unlock(philo->fork_left);
		return;
	}
	write_action(TAKE_FORK, philo->id, philo->param, philo);
	if (philo->param->nbr_philo % 2 && (get_time(philo->param) - philo->last_meal) + philo->param->time_to_eat > philo->param->time_to_die && (philo->param->time_to_eat * 2) + philo->param->time_to_sleep >= philo->param->time_to_die)
	{
	//	printf("fork too for %d time %lld last meal %lld time die %d\n",philo->id +1, get_time(philo->param), philo->last_meal, philo->param->time_to_die);
		ft_sleep(philo->param->time_to_die - (get_time(philo->param) - philo->last_meal));
		die(philo);
	}
	pthread_mutex_lock(philo->fork_right);
	if (!check_all_alive(philo->param, philo))
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return;
	}
	write_action(TAKE_FORK, philo->id, philo->param, philo);
	write_action(EATING, philo->id, philo->param, philo);
	philo_sleep(philo, philo->param->time_to_eat, 1);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void	eat_odd(t_philosopher *philo)
{
	pthread_mutex_lock(philo->fork_right);
	if (!check_all_alive(philo->param, philo))
	{
		pthread_mutex_unlock(philo->fork_right);
		return ;
	}
	write_action(TAKE_FORK, philo->id, philo->param, philo);
	pthread_mutex_lock(philo->fork_left);
	if (!check_all_alive(philo->param, philo))
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		return ;
	}
	write_action(TAKE_FORK, philo->id, philo->param, philo);
	write_action(EATING, philo->id, philo->param, philo);
	philo_sleep(philo, philo->param->time_to_eat, 1);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
}

void	algorythm_even(t_philosopher *philo)
{
	if (philo->state == THINKING)
	{
		if ((philo->id + 1) % 2)
			eat_odd(philo);
		else
			eat_even(philo);
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
