/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:14:47 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/02 10:14:58 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_is_only_number(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

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
