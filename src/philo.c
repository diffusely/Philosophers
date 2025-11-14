/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:28:17 by noavetis          #+#    #+#             */
/*   Updated: 2025/11/14 23:41:37 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_philo *philo, char *message, long long time)
{
	time = time - philo->manag->start_time;
	pthread_mutex_lock(&philo->manag->print);
	if (!philo->manag->someone_died && !philo->dead)
		printf("%lld %d %s",
				time, 
				philo->id,
				message);
	pthread_mutex_unlock(&philo->manag->print);
}

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
}

void	print_fork_taken(t_philo *philo, const char *type)
{
	long long	time;

	time = time_ms() - philo->manag->start_time;
	pthread_mutex_lock(&philo->manag->print);
	if (!philo->manag->someone_died && !philo->dead)
		printf("%lld %d has taken a %s fork\n", 
			time, philo->id, type);
	pthread_mutex_unlock(&philo->manag->print);
}

bool philo_is_dead(t_philo *philo, int flag)
{
    long long now;

    now = time_ms();
    if (now - philo->last_meal > philo->manag->args_time[DIE] && flag)
        return (true);
	if (!philo->dead && philo->meal_eaten == philo->manag->args_time[MUST_EAT] && !flag)
	{
		philo->dead = 1;
		philo->manag->died_count++;
	}
	if (philo->manag->died_count == philo->manag->philo_count && !flag)
		return (true);
    return (false);
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->manag->someone_died)
	{
		philo_eat(philo);
		pthread_mutex_lock(&philo->meal);
		philo->last_meal = time_ms();
		pthread_mutex_unlock(&philo->meal);
		print_msg(philo, "is eating\n", time_ms());
		ft_usleep(philo->manag->args_time[EAT]);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		++(philo->meal_eaten);
		print_msg(philo, "is sleeping\n", time_ms());
		ft_usleep(philo->manag->args_time[SLEEP]);
		print_msg(philo, "is thinking\n", time_ms());
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
				print_msg(manag->philos, "died\n", time_ms());
				manag->someone_died = 1;
				pthread_mutex_unlock(&manag->death);
				
				pthread_mutex_unlock(&manag->philos[i].meal);
				return (NULL);
			}
			if (philo_is_dead(&manag->philos[i], 0))
			{
				pthread_mutex_lock(&manag->death);
				manag->someone_died = 1;
				pthread_mutex_unlock(&manag->death);
				pthread_mutex_unlock(&manag->philos[i].meal);
				return (NULL);
			}
			pthread_mutex_unlock(&manag->philos[i].meal);
			i++;
		}
		usleep(300);
	}
	return (NULL);
}
