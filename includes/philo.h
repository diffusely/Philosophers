/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:11:50 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/07 21:52:21 by noavetis         ###   ########.fr       */
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

typedef struct s_philo
{
	int				id;
	int				meal_eaten;

	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_manag
{
	int				philo_count;
	int				args_time[4];
	int				someone_died;
	long			start_time;

	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	t_philo			*philos;
}	t_manag;

// libft functions
long	ft_atoi(const char *str);
int		ft_isdigit(int c);

// validation
bool	valid_input(int argc, char **argv);
bool	valid_num(int argc, char **argv);

// free
void	free_all(t_manag *manag, int flag);

// init
bool	init_all(t_manag *manag, int argc, char **argv);

#endif