/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_even.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 17:52:59 by earnaud           #+#    #+#             */
/*   Updated: 2021/09/13 16:01:52 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	odd_late_fork(t_philosopher *philo)
{
	if (philo->param->nbr_philo != 1 && philo->param->nbr_philo % 2
		&& (get_time(philo->param) - philo->last_meal)
		+ philo->param->time_to_eat > philo->param->time_to_die
		&& (philo->param->time_to_eat * 2)
		+ philo->param->time_to_sleep >= philo->param->time_to_die)
	{
		ft_sleep(philo->param->time_to_die
			- (get_time(philo->param) - philo->last_meal));
		die(philo);
	}
}
