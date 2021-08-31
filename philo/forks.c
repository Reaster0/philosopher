/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:49:27 by earnaud           #+#    #+#             */
/*   Updated: 2021/08/31 13:53:23 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	fork_create_assign_1(t_philosopher *philo)
{
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * 2);
	if (!forks)
		return (1);
	if (pthread_mutex_init(forks, NULL))
		return (1);
	if (pthread_mutex_init(forks + 1, NULL))
		return (1);
	philo->last_meal = 0;
	philo->state = THINKING;
	philo->fork_left = forks;
	philo->fork_right = forks + 1;
	return (0);
}

int	fork_create_assign(t_philosopher *philo, int nbr)
{
	int				i[2];
	pthread_mutex_t	*forks;

	if (nbr == 1)
		return (fork_create_assign_1(philo));
	forks = malloc(sizeof(pthread_mutex_t) * nbr);
	if (!forks)
		return (1);
	i[0] = 0;
	i[1] = 1;
	while (i[0] < nbr)
	{
		if (pthread_mutex_init(forks + i[0], NULL))
			return (1);
		(philo + i[0])->last_meal = 0;
		(philo + i[0])->state = THINKING;
		(philo + i[0])->fork_left = forks + i[0];
		if (i[1] == nbr)
			(philo + i[0])->fork_right = forks;
		else
			(philo + i[0])->fork_right = forks + i[1];
		i[1]++;
		i[0]++;
	}
	return (0);
}
