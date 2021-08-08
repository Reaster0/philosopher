/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 11:52:58 by earnaud           #+#    #+#             */
/*   Updated: 2021/08/08 20:26:31 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	thread_join(t_philosopher *philo, int nbr)
{
	int i;

	i = 0;
	while (i < nbr)
		if (pthread_join((philo + i++)->thread, NULL))
			return (1);
	return (0);
}

long long get_time(t_param *param)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - param->time_start);
}

int ft_error(void)
{
	printf("error: bad arguments\n");
	return (1);
}

int main(int argc, char **argv)
{
	t_philosopher *philo;
	//check error
	if (ft_check_error(argc, argv + 1))
		return (ft_error());
	if (set_philo(&philo, argv))
		return (1);
	if (fork_create_assign(philo, philo->param->nbr_philo))
		return (1);
	philo->param->time_start = get_time(philo->param);
	if (thread_create(philo, philo->param->nbr_philo))
		return (1);
	if (thread_join(philo, philo->param->nbr_philo))
		return (1);
	return (0);
}