/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 11:52:58 by earnaud           #+#    #+#             */
/*   Updated: 2021/08/27 15:24:17 by earnaud          ###   ########.fr       */
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

int free_all(t_philosopher **philo, int no_fork)
{
	int i;
	void *to_free1;
	void *to_free2;

	to_free1 = *philo;
	if (!no_fork)
		to_free2 = (*philo)->fork_left;
	i = (*philo)->param->nbr_philo;
	pthread_mutex_destroy((*philo)->param->alive_mutex);
	free((*philo)->param->alive_mutex);
	free((*philo)->param);
	while (i > 0)
	{
		pthread_mutex_destroy((*philo)->fork_right);
		(*philo)++;
		i--;
	}
	free(to_free1);
	if (!no_fork)
		free(to_free2);
	return (1);
}

int main(int argc, char **argv)
 {
	t_philosopher *philo;

	if (ft_check_error(argc, argv + 1))
		return (ft_error());
	if (set_philo(&philo, argv))
		return (free_all(&philo, 1));
	if (fork_create_assign(philo, philo->param->nbr_philo))
		return (free_all(&philo, 0));
	philo->param->time_start = get_time(philo->param);
	if (thread_create(philo, philo->param->nbr_philo))
		return (free_all(&philo, 0));
	if (thread_join(philo, philo->param->nbr_philo))
		return (free_all(&philo, 0));
	free_all(&philo, 0);
	return (0);
}