/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:28:17 by noavetis          #+#    #+#             */
/*   Updated: 2025/11/08 23:19:14 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_fork_taken(philo, "right");
		pthread_mutex_lock(philo->l_fork);
		print_fork_taken(philo, "left");
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_fork_taken(philo, "left");
		pthread_mutex_lock(philo->r_fork);
		print_fork_taken(philo, "right");
	}
	
	pthread_mutex_lock(&philo->meal);
	++(philo->meal_eaten);
	philo->last_meal = time_ms();
	pthread_mutex_unlock(&philo->meal);
	
	printf("%lld %d is eating\n", time_ms() - philo->manag->start_time, philo->id);
	usleep(philo->manag->args_time[EAT] * 1000);
	
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	print_fork_taken(t_philo *philo, const char *type)
{
	printf("%lld %d has taken a %s fork\n", time_ms() - philo->manag->start_time, philo->id, type);
}


void	philo_sleep(t_philo *philo)
{
	printf("%lld %d is sleeping\n", time_ms() - philo->manag->start_time, philo->id);
	usleep(philo->manag->args_time[SLEEP] * 1000);
}

void	philo_think(t_philo *philo)
{
	printf("%lld %d is thinking\n", time_ms() - philo->manag->start_time, philo->id);
}

bool philo_is_dead(t_philo *philo)
{
    long long now;

    now = time_ms();
    if (now - philo->last_meal > philo->manag->args_time[DIE])
        return true;
	if (philo->meal_eaten == philo->manag->args_time[MUST_EAT])
		return true;
    return false;
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		

		pthread_mutex_lock(&philo->meal);
		if (philo_is_dead(philo))
			break;
		pthread_mutex_unlock(&philo->meal);
	}
	return (NULL);
}
