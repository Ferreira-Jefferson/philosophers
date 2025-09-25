/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_decimal_places.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:56:35 by jtertuli          #+#    #+#             */
/*   Updated: 2025/07/29 17:00:11 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_count_decimal_places(long long int n)
{
	unsigned long long int	nb;
	int						counter;

	nb = n;
	if (n < 0)
		nb = n * -1;
	counter = (n <= 0);
	while (nb > 0)
	{
		counter++;
		nb /= 10;
	}
	return (counter);
}
