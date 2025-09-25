/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:30:52 by jtertuli          #+#    #+#             */
/*   Updated: 2025/07/28 13:52:23 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void **alloc, size_t cur_sz, size_t new_sz, size_t t_sz)
{
	void	*p;
	size_t	new_total_bytes;

	if (!new_sz)
		return (ft_to_free(alloc));
	if (t_sz && new_sz > (size_t)-1 / t_sz)
		return (NULL);
	new_total_bytes = new_sz * t_sz;
	if (!*alloc)
		return (malloc(new_total_bytes));
	if (!new_total_bytes)
		return (ft_to_free(alloc));
	p = malloc(new_total_bytes);
	if (new_total_bytes > (cur_sz * t_sz))
		new_total_bytes = (cur_sz * t_sz);
	ft_memmove(p, *alloc, new_total_bytes);
	ft_to_free(alloc);
	return (p);
}
