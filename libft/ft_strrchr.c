/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 09:04:45 by jtertuli          #+#    #+#             */
/*   Updated: 2025/07/14 16:20:15 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*aux_s;
	char	*occurrence;

	aux_s = (char *) s;
	occurrence = NULL;
	while (*aux_s)
	{
		if (*aux_s == (char)c)
			occurrence = aux_s;
		aux_s++;
	}
	if (c == '\0')
		occurrence = aux_s;
	return (occurrence);
}
