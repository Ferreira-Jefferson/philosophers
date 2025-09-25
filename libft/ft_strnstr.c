/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:14:47 by jtertuli          #+#    #+#             */
/*   Updated: 2025/07/14 17:37:26 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*aux_big;
	char	*aux_little;
	size_t	i;
	size_t	j;

	aux_big = (char *) big;
	aux_little = (char *) little;
	if (ft_strlen(aux_little) == 0)
		return (aux_big);
	i = 0;
	while (aux_big[i] && i < len)
	{
		j = 0;
		if (aux_big[i] == aux_little[j])
		{
			while (aux_little[j] == aux_big[i + j] && (i + j) < len)
				j++;
			if (aux_little[j] == '\0')
				return (&aux_big[i]);
		}
		i++;
	}
	return (NULL);
}
