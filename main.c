/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 11:52:58 by earnaud           #+#    #+#             */
/*   Updated: 2021/07/30 19:46:56 by earnaud          ###   ########.fr       */
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

int main(int argc, char **argv)
{
	t_philosopher *philo;
	//check error
	
	if (set_philo(&philo, argv))
		return (1);
	if (fork_create_assign(philo, philo->param->nbr_philo))
		return (1);
	if (thread_create(philo, philo->param->nbr_philo))
		return (1);
	if (thread_join(philo, philo->param->nbr_philo))
		return (1);
	return (0);
}