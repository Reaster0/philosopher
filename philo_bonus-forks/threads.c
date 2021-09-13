/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 16:11:51 by earnaud           #+#    #+#             */
/*   Updated: 2021/09/13 16:46:24 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	thread_detach(t_philosopher *philo, int nbr)
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
