/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 11:44:58 by jtertuli          #+#    #+#             */
/*   Updated: 2025/07/14 08:14:03 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *b1, const void *b2, size_t len)
{
	unsigned char	*aux_b1;
	unsigned char	*aux_b2;

	aux_b1 = (unsigned char *) b1;
	aux_b2 = (unsigned char *) b2;
	while (len--)
	{
		if (*aux_b1 != *aux_b2)
			return (*aux_b1 - *aux_b2);
		aux_b1++;
		aux_b2++;
	}
	return (0);
}
