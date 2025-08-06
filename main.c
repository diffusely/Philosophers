/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:24:19 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/06 18:27:21 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

// 1 - number phlo
// 2 - time to die
// 3 - time to sleep
// 4 - must eat

// (ms) (number philo) (state)
int main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Invalid arguments!\n");
		return (-1);
	}
	return (0);
}

