/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:27:39 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/11 16:49:35 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static int	ft_populate_buffer(const char *base, int id, char *buffer)
{
	int	i;

	i = 0;
	while (base[i])
	{
		buffer[i] = base[i];
		i++;
	}
	if (id == 0)
	{
		buffer[i++] = '0';
		buffer[i] = '\0';
	}
	return (i);
}

void	ft_generate_sem_name(const char *base, int id, char *buffer)
{
	char	nbr[11];
	int		k;
	int		i;
	int		j;

	i = ft_populate_buffer(base, id, buffer);
	if (id == 0)
		return ;
	j = 0;
	k = id;
	while (k > 0)
	{
		nbr[j++] = (k % 10) + '0';
		k /= 10;
	}
	while (j > 0)
		buffer[i++] = nbr[--j];
	buffer[i] = '\0';
}

void	ft_print_message(t_philo *philo, char *message)
{
	long	timestamp;

	sem_wait(philo->common->sem_print);
	timestamp = ft_get_time_ms() - philo->common->start_time;
	printf("%ld %d %s\n", timestamp, philo->id_philo + 1, message);
	sem_post(philo->common->sem_print);
}

long	ft_get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
