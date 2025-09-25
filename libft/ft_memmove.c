/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:37:22 by jtertuli          #+#    #+#             */
/*   Updated: 2025/07/14 08:13:22 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*aux_dst;
	unsigned char	*aux_src;

	aux_dst = (unsigned char *) dst;
	aux_src = (unsigned char *) src;
	if (aux_dst <= aux_src)
		return (ft_memcpy(aux_dst, aux_src, len));
	while (len--)
		aux_dst[len] = aux_src[len];
	return (dst);
}
