/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:30:40 by noavetis          #+#    #+#             */
/*   Updated: 2025/11/16 19:55:23 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long long ms)
{
	long	start;

	start = time_ms();
	while ((time_ms() - start) < ms)
		usleep(50);
}

void	free_all(t_manag *manag, int flag)
{
	int	i;

	i = 0;
	if (manag->philos)
	{
		while (i < manag->philo_count)
			pthread_mutex_destroy(&manag->forks[i++]);
		free(manag->philos);
		manag->philos = NULL;
	}
	if (flag)
		pthread_mutex_destroy(&manag->print);
	if (manag->forks)
	{
		free(manag->forks);
		manag->forks = NULL;
	}
}
