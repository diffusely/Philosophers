/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:52:05 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/07 20:09:04 by noavetis         ###   ########.fr       */
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
