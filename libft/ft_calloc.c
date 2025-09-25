/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:31:30 by jtertuli          #+#    #+#             */
/*   Updated: 2025/08/07 10:04:23 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	void	*p;

	if (!size || !number)
		return (malloc(1));
	if (size && number > (size_t)-1 / size)
		return (NULL);
	p = (void *) malloc(number * size);
	if (!p)
		return (NULL);
	p = ft_memset(p, 0, number * size);
	return (p);
}
