/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 11:52:58 by earnaud           #+#    #+#             */
/*   Updated: 2021/07/27 20:14:47 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int mails = 0;
pthread_mutex_t mutex_test;

void *routine()
{
	int i = 0;
	while (i < 1000000)
	{
		pthread_mutex_lock(&mutex_test);
		i++;
		mails++;
		pthread_mutex_unlock(&mutex_test);
	}
}

int main()
{
	pthread_t thread1, thread2;
	pthread_mutex_init(&mutex_test, NULL);
	pthread_create(&thread1, NULL, &routine, NULL);
	pthread_create(&thread2, NULL, &routine, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("mails = %d", mails);
	pthread_mutex_destroy(&mutex_test);
	return (0);
}