/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:55:19 by jtertuli          #+#    #+#             */
/*   Updated: 2025/07/30 12:18:10 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int		number;
	char	*result;

	if (!ft_is_valid_base(base_from) || !ft_is_valid_base(base_to))
		return (NULL);
	number = ft_atoi_base(nbr, base_from);
	result = ft_itoa_base(number, base_to);
	return (result);
}
