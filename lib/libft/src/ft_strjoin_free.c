/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 22:27:00 by noavetis          #+#    #+#             */
/*   Updated: 2025/05/09 23:19:11 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*str;
	size_t	size;
	size_t	i;

	if (!s1)
		return (NULL);
	if (!s2)
		return (free(s1), NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (free(s1), NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	while (s2 && *s2)
	{
		str[i] = *(s2++);
		i++;
	}
	str[i] = '\0';
	return (free(s1), str);
}
