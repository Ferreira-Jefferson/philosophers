/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:58:35 by jtertuli          #+#    #+#             */
/*   Updated: 2025/07/14 17:36:02 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*p;
	size_t	size;

	size = ft_strlen(str) + 1;
	p = (char *) malloc(size * sizeof(char));
	if (!p)
		return (NULL);
	p = ft_memcpy(p, str, size);
	return (p);
}
