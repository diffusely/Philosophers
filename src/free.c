/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 21:19:27 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/07 21:48:04 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
