/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 11:26:21 by jtertuli          #+#    #+#             */
/*   Updated: 2025/07/14 08:29:30 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *b, int c, size_t len)
{
	unsigned char	*aux_b;

	aux_b = (unsigned char *) b;
	while (len--)
	{
		if (*aux_b == (unsigned char) c)
			return (aux_b);
		aux_b++;
	}
	return (NULL);
}
