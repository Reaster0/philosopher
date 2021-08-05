/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 11:52:58 by earnaud           #+#    #+#             */
/*   Updated: 2021/08/05 15:41:44 by earnaud          ###   ########.fr       */
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

long long unsigned get_time(t_param *param)
{
	struct timeval time;
	long long unsigned time_value;
	gettimeofday(&time, NULL);
	time_value = time.tv_sec * 1000 + time.tv_usec / 1000;
	time_value = time_value - param->time_start;
	return (time_value);
}

void ft_test(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	printf("le temps = %ld\n", (time.tv_sec * 1000 + time.tv_usec / 1000));
}

int main(int argc, char **argv)
{
	t_philosopher *philo;
	long long unsigned temp;
	//check error
	
	t_param param;
	param.time_start = 0;
	param.time_start = get_time(&param);
	printf("on commence avec temp = %lld\n", param.time_start);
	usleep(1000);
	temp = get_time(&param);
	printf("maintenant le temp = %llu\n", get_time(&param) * 1000);
	return 0;

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