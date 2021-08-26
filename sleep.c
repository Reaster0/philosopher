/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 17:56:17 by earnaud           #+#    #+#             */
/*   Updated: 2021/08/26 18:29:22 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long get_time_temp(long long time_start)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - time_start);
}

void test_time(void)
{
	long long initial_time;
	 initial_time = get_time_temp(0);

	while (1)
	{
		printf("%lld\n", get_time_temp(initial_time));
		ft_sleep(1);
	}
}

void ft_sleep(long milliseconds)
{
	struct timeval tval_before, tval_after, tval_result;
	double time_elapsed;
    long counter = 0;
    int stop = 0;
   
    gettimeofday(&tval_before, NULL);
    while(!stop)
    {
        gettimeofday(&tval_after, NULL);
        timersub(&tval_after, &tval_before, &tval_result); //modify this later
        time_elapsed = (double)tval_result.tv_sec + ((double)tval_result.tv_usec/1000000.0f);
        while(time_elapsed < 0.001)  //1ms; you can change your desired time interval here
        {
            gettimeofday(&tval_after, NULL);
            timersub(&tval_after, &tval_before, &tval_result);
            time_elapsed = (double)tval_result.tv_sec + ((double)tval_result.tv_usec/1000000.0f);
        }
        gettimeofday(&tval_before, NULL);
        if (counter == milliseconds)
            stop = 1;    
        else
            counter++;
    }
}