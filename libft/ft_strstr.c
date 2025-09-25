/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:14:47 by jtertuli          #+#    #+#             */
/*   Updated: 2025/07/13 15:58:27 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	char	*aux_big;
	char	*aux_little;

	aux_big = (char *) big;
	aux_little = (char *) little;
	if (ft_strlen(aux_little) == 0)
		return (aux_big);
	while (*aux_big)
	{
		aux_big = ft_strchr(aux_big, aux_little[0]);
		if (aux_big == NULL)
			return (NULL);
		if (ft_strncmp(aux_big, aux_little, ft_strlen(aux_little)) == 0)
			return (aux_big);
		aux_big++;
	}
	return (NULL);
}
