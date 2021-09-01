/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 15:35:04 by earnaud           #+#    #+#             */
/*   Updated: 2021/09/01 18:07:06 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int in_main_process(int *process, int nbr)
{
	int i = 0;

	while (i < nbr)
	{
		if (!process[i])
			return (0);
		i++;
	}
	return (1);
}

int process_create(t_philosopher *philo)
{
	int *process;
	int i;

	i = 0;
	process = malloc (sizeof(int) * philo->param->nbr_philo);
	if (!process)
		return (1);
	while (i < philo->param->nbr_philo)
	{
		process[i] = fork();
		if (process[i] == -1)
			return (1);
		if (!process[i])
		{
			routine(philo + i);
			//child process
			exit (0) ;
		}
		i++;
	}
	wait(NULL);
	i = 0;
	while (i < philo->param->nbr_philo)
	{
		kill(process[i], SIGTERM);
		i++;
	}
	return (0);
}