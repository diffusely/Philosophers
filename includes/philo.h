/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:11:50 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/07 16:13:34 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdbool.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct	s_philo
{
	int	state_time[5]; // if 5 is -1 given 4 param
	
} t_philo;

// libft functions
long	ft_atoi(const char *str);
int		ft_isdigit(int c);

// validation
bool	valid_input(int argc, char **argv);

#endif