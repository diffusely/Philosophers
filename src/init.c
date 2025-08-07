/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:17:02 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/07 21:56:15 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_manag(t_manag *manag, int argc, char **argv)
{
	manag->philo_count = ft_atoi(argv[1]);
	manag->args_time[DIE] = ft_atoi(argv[2]);
	manag->args_time[EAT] = ft_atoi(argv[3]);
	manag->args_time[SLEEP] = ft_atoi(argv[4]);
	if (argc == 6)
		manag->args_time[MUST_EAT] = ft_atoi(argv[5]);
	else
		manag->args_time[MUST_EAT] = -1;
	manag->someone_died = 0;
	manag->start_time = 0;
	manag->philos = malloc(sizeof(t_philo) * (manag->philo_count));
	if (!manag->philos)
	{
		printf("Bad alloc for philos!\n");
		return (false);
	}
	manag->forks = malloc(sizeof(pthread_mutex_t) * manag->philo_count);
	if (!manag->forks)
	{
		free(manag->philos);
		printf("Bad alloc for forks!\n");
		return (false);
	}
	return (true);
}

static void	init_philo(t_manag *manag)
{
	int	i;

	i = 0;
	while (i < manag->philo_count)
	{
		manag->philos[i].id = i + 1;
		manag->philos[i].meal_eaten = 0;
		manag->philos[i].left_fork = &manag->forks[i];
		manag->philos[i].right_fork = &manag->forks[(i + 1) % manag->philo_count];
		++i;
	}
}

static bool	init_forks(t_manag *manag)
{
	int	i;

	i = -1;
	while (++i < manag->philo_count)
	{
		if (pthread_mutex_init(&manag->forks[i], NULL) != 0)
		{
			printf("Mutex init failed\n");
			while (--i >= 0)
				pthread_mutex_destroy(&manag->forks[i]);
			free(manag->forks);
			free(manag->philos);
			return (false);
		}
	}
	i = 0;
	if (pthread_mutex_init(&manag->print, NULL) != 0)
	{
		printf("Print mutex init failed\n");
		free_all(manag, 0);
		return (false);
	}
	return (true);
}

bool	init_all(t_manag *manag, int argc, char **argv)
{
	if (!init_manag(manag, argc, argv))
		return (false);
	if (!init_forks(manag))
		return (false);
	init_philo(manag);
	return (true);
}
