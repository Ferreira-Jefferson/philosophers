/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:00:18 by jtertuli          #+#    #+#             */
/*   Updated: 2025/07/23 12:49:47 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	unsigned int	nb;
	int				signal;

	if (*nptr == '\0')
		return (0);
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	signal = 1;
	if (*nptr == '+' || *nptr == '-' )
	{
		if (*nptr == '-')
			signal = -1;
		nptr++;
	}
	nb = 0;
	while (ft_isdigit(*nptr))
	{
		nb = (nb * 10) + (*nptr - '0');
		if (signal == -1 && nb >= INT_MAX)
			return (INT_MIN);
		if (nb > INT_MAX)
			return (INT_MAX);
		nptr++;
	}
	return (nb * signal);
}
