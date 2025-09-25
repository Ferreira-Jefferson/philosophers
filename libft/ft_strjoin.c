/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:17:10 by jtertuli          #+#    #+#             */
/*   Updated: 2025/07/15 11:49:40 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*aux_s1;
	char	*join;
	size_t	size_join;

	if (!s1)
		return (NULL);
	aux_s1 = (char *) s1;
	if (!s2)
		return (aux_s1);
	size_join = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = (char *) ft_calloc(size_join, sizeof(char));
	if (!join)
		return (NULL);
	ft_strlcat(join, s1, size_join);
	ft_strlcat(join, s2, size_join);
	return (join);
}
