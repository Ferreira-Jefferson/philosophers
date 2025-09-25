/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_upper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:38:49 by jtertuli          #+#    #+#             */
/*   Updated: 2025/08/07 11:03:42 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_hex_upper(va_list args)
{
	char	*hex_ptr;
	int		len;

	hex_ptr = ft_itoa_base(va_arg(args, unsigned int), "0123456789ABCDEF");
	ft_putstr_fd(hex_ptr, 1);
	len = ft_strlen(hex_ptr);
	ft_to_free((void **)&hex_ptr);
	return (len);
}
