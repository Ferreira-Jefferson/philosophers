/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:00:54 by jtertuli          #+#    #+#             */
/*   Updated: 2025/07/30 13:09:07 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_base(char *nbr, char *base)
{
	int	result;
	int	base_len;
	int	sign;
	int	j;

	result = 0;
	base_len = ft_strlen(base);
	sign = 1;
	while (ft_isspace(*nbr))
		nbr++;
	if (*nbr == '-' || *nbr == '+')
		if (*nbr++ == '-')
			sign = -1;
	while (*nbr)
	{
		j = 0;
		while (base[j] && base[j] != *nbr)
			j++;
		if (base[j] == '\0')
			break ;
		result = result * base_len + j;
		nbr++;
	}
	return (result * sign);
}
