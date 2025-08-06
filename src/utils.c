/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:30:40 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/06 18:38:50 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phlo.h"

long	ft_atoi(const char *str)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	while (*str && ((*str >= 9 && *str <= 13) || (*str == ' ')))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		num = (10 * num) + *str - '0';
		str++;
	}
	return (num * sign);
}
