/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:11:50 by noavetis          #+#    #+#             */
/*   Updated: 2025/11/16 20:02:45 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdbool.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

# define DIE 0
# define EAT 1
# define SLEEP 2
# define MUST_EAT 3

typedef struct s_manag	t_manag;

typedef struct s_philo
{
	int				id;
	int				meal_eaten;
	int				dead;
	long long		last_meal;
	t_manag			*manag;
	pthread_mutex_t	meal;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

typedef struct s_manag
{
	int				philo_count;
	int				args_time[4];
	int				someone_died;
	int				died_count;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_t		checker;
	t_philo			*philos;
}	t_manag;

long	ft_atoi(const char *str);
int		ft_isdigit(int c);
bool	valid_input(int argc, char **argv);
bool	valid_num(int argc, char **argv);
void	free_all(t_manag *manag, int flag);
bool	init_all(t_manag *manag, int argc, char **argv);
long	time_ms(void);
void	ft_usleep(long long ms);
void	*philo_routine(void *arg);
void	*check(void *arg);
bool	philo_is_dead(t_philo *philo, int flag);
void	print_msg(t_philo *philo, char *message, long long time);
void	print_fork_taken(t_philo *philo, const char *type);

#endif