/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:35:57 by jtertuli          #+#    #+#             */
/*   Updated: 2025/07/12 07:50:26 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char	*aux_dst;
	unsigned char	*aux_src;

	aux_dst = (unsigned char *) dst;
	aux_src = (unsigned char *) src;
	while (len--)
	{
		*aux_dst = *aux_src;
		aux_dst++;
		aux_src++;
	}
	return (dst);
}
