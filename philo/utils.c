/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 08:21:34 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/03 16:00:00 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_print_message(t_philo *philo, char *message)
{
	long	timestamp;
	int		should_print;

	pthread_mutex_lock(&philo->common->shutdown_mutex);
	should_print = !philo->common->shutdown;
	pthread_mutex_unlock(&philo->common->shutdown_mutex);

	// Só printa se não estiver em shutdown (exceto mensagem de morte)
	if (should_print || message[0] == 'd') // "died"
	{
		pthread_mutex_lock(&philo->common->printf_mutex);
		pthread_mutex_lock(&philo->common->start_time_mutex);
		timestamp = ft_get_time_ms() - philo->common->start_time;
		printf("%ld %d %s\n", timestamp, philo->id_philo + 1, message);
		pthread_mutex_unlock(&philo->common->start_time_mutex);
		pthread_mutex_unlock(&philo->common->printf_mutex);
	}
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
	pthread_mutex_destroy(&common->start_time_mutex);
}

void	ft_free_common(t_common **common)
{
	free((*common)->forks_mutex);
	free(*common);
}

long	ft_get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}