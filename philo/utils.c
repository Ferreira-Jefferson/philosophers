/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 08:21:34 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/01 15:15:16 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_print_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->common->printf_mutex);
	printf("%ld %d %s\n", ft_get_time_ms(), philo->id_philo + 1, message);
	pthread_mutex_unlock(&philo->common->printf_mutex);
}

void	ft_join(int quantity, pthread_t *thr_philos, pthread_t *thr_monitor)
{
	int	i;

	i = 0;
	while (i < quantity)
	{
		pthread_join(thr_philos[i], NULL);
		i++;
	}
	pthread_join(*thr_monitor, NULL);
}

void	ft_destroy_mutex(t_common *common)
{
	int	i;

	i = 0;
	while (i < common->number_of_philosophers)
	{
		pthread_mutex_destroy(&common->forks_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&common->printf_mutex);
	pthread_mutex_destroy(&common->shutdown_mutex);
}

void	ft_free_common(t_common **common)
{
	ft_to_free((void **) &(*common)->forks_mutex);
	ft_to_free((void **) common);
}

long	ft_get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
