/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:28:17 by noavetis          #+#    #+#             */
/*   Updated: 2025/11/09 19:03:13 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	if (philo->manag->someone_died)
		return;
		
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
	
	if (!philo->manag->someone_died)
		printf("%lld %d is eating\n", time_ms() - philo->manag->start_time, philo->id);
	usleep(philo->manag->args_time[EAT] * 1000);
	
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	print_fork_taken(t_philo *philo, const char *type)
{
	if (!philo->manag->someone_died)
		printf("%lld %d has taken a %s fork\n", 
			time_ms() - philo->manag->start_time, philo->id, type);
}


void	philo_sleep(t_philo *philo)
{
	if (!philo->manag->someone_died)
		printf("%lld %d is sleeping\n", 
			time_ms() - philo->manag->start_time, philo->id);
	usleep(philo->manag->args_time[SLEEP] * 1000);
}

void	philo_think(t_philo *philo)
{
	if (!philo->manag->someone_died)
		printf("%lld %d is thinking\n", 
			time_ms() - philo->manag->start_time, philo->id);
}

bool philo_is_dead(t_philo *philo, int flag)
{
    long long now;

    now = time_ms();
    if (now - philo->last_meal > philo->manag->args_time[DIE] && flag)
        return true;
	if (philo->meal_eaten == philo->manag->args_time[MUST_EAT] && !flag)
		return true;
    return false;
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->manag->someone_died)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
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
			pthread_mutex_lock(&manag->philos[i].meal);
			if (philo_is_dead(&manag->philos[i], 1))
			{
				pthread_mutex_lock(&manag->death);
				if (!manag->someone_died)
				{
					manag->someone_died = 1;
					printf("%lld %d died\n", time_ms() - manag->start_time, manag->philos[i].id);
				}
				pthread_mutex_unlock(&manag->death);
				pthread_mutex_unlock(&manag->philos[i].meal);
				return (NULL);
			}
			if (philo_is_dead(&manag->philos[i], 0))
			{
				pthread_mutex_lock(&manag->death);
				if (!manag->someone_died)
					manag->someone_died = 1;
				pthread_mutex_unlock(&manag->death);
				pthread_mutex_unlock(&manag->philos[i].meal);
				return (NULL);
			}
			pthread_mutex_unlock(&manag->philos[i].meal);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
