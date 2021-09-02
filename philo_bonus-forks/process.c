/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 15:35:04 by earnaud           #+#    #+#             */
/*   Updated: 2021/09/02 16:02:35 by earnaud          ###   ########.fr       */
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
	process = malloc(sizeof(int) * philo->param->nbr_philo);
	if (!process)
		return (1);
	philo->param->time_start = get_time(philo->param);
	sem_wait(philo->param->starting_block);
	while (i < philo->param->nbr_philo)
	{
		
		process[i] = fork();
		//if (process[i] == -1)
		//	return (1);
		if (!process[i])
		{
			//child process
			routine(philo + i);
		}
		i++;
	}
	sem_post(philo->param->starting_block);
	//setup_sem_launching(philo->param->starting_block, philo->param->nbr_philo);
	wait(NULL);
	i = 0;
	while (i < philo->param->nbr_philo)
	{
		kill(process[i], SIGTERM);
		i++;
	}
	free(process);
	return (0);
}