/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:49:27 by earnaud           #+#    #+#             */
/*   Updated: 2021/08/31 19:35:22 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// int	fork_create_assign_1(t_philosopher *philo)
// {
// 	pthread_mutex_t	*forks;

// 	forks = malloc(sizeof(pthread_mutex_t) * 2);
// 	if (!forks)
// 		return (1);
// 	if (pthread_mutex_init(forks, NULL))
// 		return (1);
// 	if (pthread_mutex_init(forks + 1, NULL))
// 		return (1);
// 	philo->last_meal = 0;
// 	philo->state = THINKING;
// 	philo->fork_left = forks;
// 	philo->fork_right = forks + 1;
// 	return (0);
// }

int	fork_create_assign(t_philosopher *philo, int nbr)
{
	int				i;
	sem_t			*forks;

	i = 0;
	sem_unlink("forks");
	forks = sem_open("forks", O_CREAT, S_IRWXU, nbr);
	if (forks == SEM_FAILED)
		return (1);
	while (i < nbr)
	{
		(philo + i)->last_meal = 0;
		(philo + i)->state = THINKING;
		(philo + i)->forks = forks;
		i++;
	}
	return (0);
}
