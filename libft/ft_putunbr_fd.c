/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:57:48 by jtertuli          #+#    #+#             */
/*   Updated: 2025/07/29 12:33:49 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putunbr_fd(unsigned int n, int fd)
{
	unsigned long int	ul;

	ul = n;
	if (ul < 10)
		return (ft_putchar_fd(ul + '0', fd));
	ft_putunbr_fd(ul / 10, fd);
	ft_putchar_fd((ul % 10) + '0', fd);
}
