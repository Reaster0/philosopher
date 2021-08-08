/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 15:56:24 by earnaud           #+#    #+#             */
/*   Updated: 2021/08/08 20:27:44 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
int	other_than_num(const char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

int ft_check_error(int argc, char **argv)
{
	long temp;
	
	if (argc <= 4 || argc >= 6)
		return (1);
	while (*argv)
	{
		if (other_than_num(*argv))
			return (1);
		temp = ft_atoi(*argv);
		if (temp > 2147483647 || temp < -2147483648 || !temp)
			return (1);
		argv++;
	}
	return (0);
}