/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:24:19 by noavetis          #+#    #+#             */
/*   Updated: 2025/11/08 21:39:49 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_manag	manag;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid arguments!\n");
		return (-1);
	}
	if (!valid_input(argc, argv) || !valid_num(argc, argv))
	{
		printf("Invalid input!\n");
		return (-1);
	}
	if (!init_all(&manag, argc, argv))
		return (-1);
	free_all(&manag, 1);
	return (0);
}
