/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 09:24:55 by jtertuli          #+#    #+#             */
/*   Updated: 2025/07/14 14:28:34 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t len)
{
	unsigned char	*aux_s1;
	unsigned char	*aux_s2;

	if (len == 0)
		return (0);
	aux_s1 = (unsigned char *) s1;
	aux_s2 = (unsigned char *) s2;
	while (*aux_s1 && --len)
	{
		if (*aux_s1 != *aux_s2)
			return (*aux_s1 - *aux_s2);
		aux_s1++;
		aux_s2++;
	}
	return (*aux_s1 - *aux_s2);
}
