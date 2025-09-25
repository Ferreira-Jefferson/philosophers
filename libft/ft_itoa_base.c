/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:01:43 by jtertuli          #+#    #+#             */
/*   Updated: 2025/07/30 12:16:30 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*create_string_ull(unsigned long int nbr, char *base, int len)
{
	size_t	base_len;
	char	*result;

	base_len = ft_strlen(base);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (nbr == 0)
		result[--len] = base[0];
	while (nbr > 0)
	{
		result[--len] = base[nbr % base_len];
		nbr /= base_len;
	}
	return (result);
}

char	*ft_itoa_base(unsigned long int nbr, char *base)
{
	int					len;
	unsigned long int	temp;
	size_t				base_len;

	len = 1;
	temp = nbr;
	base_len = ft_strlen(base);
	while (temp >= (unsigned long int)base_len)
	{
		temp /= base_len;
		len++;
	}
	return (create_string_ull(nbr, base, len));
}
