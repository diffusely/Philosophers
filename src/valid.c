/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:52:05 by noavetis          #+#    #+#             */
/*   Updated: 2025/11/16 20:01:02 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	valid_input(int argc, char **argv)
{
	int	i;
	int	j;

	if (!argv)
		return (false);
	i = 1;
	while (i < argc)
	{
		j = 0;
		if (!argv[i][j])
			return (false);
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (false);
			++j;
		}
		++i;
	}
	return (true);
}

bool	valid_num(int argc, char **argv)
{
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > 200)
		return (false);
	if (ft_atoi(argv[2]) <= 0)
		return (false);
	if (ft_atoi(argv[3]) <= 0)
		return (false);
	if (ft_atoi(argv[4]) <= 0)
		return (false);
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
		return (false);
	return (true);
}

static int	help_check(t_manag	*manag, int i)
{
	pthread_mutex_lock(&manag->philos[i].meal);
	if (philo_is_dead(&manag->philos[i], 1))
	{
		pthread_mutex_lock(&manag->death);
		print_msg(manag->philos, "died\n", time_ms());
		manag->someone_died = 1;
		pthread_mutex_unlock(&manag->death);
		pthread_mutex_unlock(&manag->philos[i].meal);
		return (1);
	}
	if (philo_is_dead(&manag->philos[i], 0))
	{
		pthread_mutex_lock(&manag->death);
		manag->someone_died = 1;
		pthread_mutex_unlock(&manag->death);
		pthread_mutex_unlock(&manag->philos[i].meal);
		return (1);
	}
	pthread_mutex_unlock(&manag->philos[i].meal);
	return (0);
}

void	*check(void *arg)
{
	t_manag	*manag;
	int		i;

	manag = (t_manag *)arg;
	while (!manag->someone_died)
	{
		i = 0;
		while (i < manag->philo_count && !manag->someone_died)
		{
			if (help_check(manag, i))
				return (NULL);
			i++;
		}
		usleep(300);
	}
	return (NULL);
}
