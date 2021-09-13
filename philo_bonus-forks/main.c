/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 11:52:58 by earnaud           #+#    #+#             */
/*   Updated: 2021/09/13 11:47:34 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int thread_detach(t_philosopher *philo, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr)
		if (pthread_detach((philo + i++)->thread))
			return (1);
	return (0);
}

int	thread_join(t_philosopher *philo, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr)
		if (pthread_join((philo + i++)->thread, NULL))
			return (1);
	return (0);
}

long long	get_time(t_param *param)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - param->time_start);
}

int	ft_error(void)
{
	write(STDERR_FILENO, "error: bad arguments\n", 22);
	return (1);
}

int	free_all(t_philosopher **philo)
{
	sem_close((*philo)->param->sem_alive);
	free((*philo)->param->id_list);
	free((*philo)->param);
	sem_close((*philo)->forks);
	free(*philo);
	return (1);
}

int	main(int argc, char **argv)
{
	t_philosopher	*philo;

	if (ft_check_error(argc, argv + 1))
		return (ft_error());
	if (set_philo(&philo, argv))
		return (free_all(&philo));
	if (fork_create_assign(philo, philo->param->nbr_philo))
		return (free_all(&philo));
	//philo->param->time_start = get_time(philo->param);
	//if (process_create(philo))
	//	return (free_all(&philo));
	if (thread_create(philo, philo->param->nbr_philo))
		return (free_all(&philo));
	if (thread_join(philo, philo->param->nbr_philo))
		return (free_all(&philo));
	if (thread_detach(philo, philo->param->nbr_philo))
		return (free_all(&philo));
	free_all(&philo);
	return (0);
}
