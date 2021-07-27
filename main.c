/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 11:52:58 by earnaud           #+#    #+#             */
/*   Updated: 2021/07/27 15:19:20 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
	
	int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void	*routine(void *arg)
{
	printf("%d ", *(int *)arg);
}

int main()
{
	pthread_t thread[10];
	int i;
	i = 0;
	while (i < 10)
	{
		i++;
		if (pthread_create(&thread[i], NULL, &routine, &i))
			perror("error with threads");
	}
	i = 0;
	while(i < 10)
	{
		i++;
		if (pthread_join(thread[i], NULL))
			perror("error with threads join");
	}
	return (0);
}