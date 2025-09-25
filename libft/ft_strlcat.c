/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:51:42 by jtertuli          #+#    #+#             */
/*   Updated: 2025/07/23 12:43:29 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_size;
	size_t	src_size;
	size_t	i;

	if (!dstsize)
		return (ft_strlen(src));
	i = 0;
	src_size = ft_strlen(src);
	dst_size = ft_strlen(dst);
	if (dst_size >= dstsize)
		return (dstsize + src_size);
	while (dst_size < (dstsize - 1) && src[i])
	{
		dst[dst_size] = src[i++];
		dst_size++;
	}
	src_size -= i;
	dst[dst_size] = '\0';
	return (dst_size + src_size);
}
