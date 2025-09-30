/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 08:21:34 by jtertuli          #+#    #+#             */
/*   Updated: 2025/09/30 17:01:42 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_validation(int argc, char *argv[])
{
	int	i;

	if (argc == 1 || (argc < 5 || argc > 6))
		return (1);
	i = 1;
	while (i < argc)
	{
		if (!ft_is_only_number(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_join(int quantity, pthread_t *thr_philos)
{
	int	i;

	i = 0;
	while (i < quantity)
	{
		pthread_join(thr_philos[i], NULL);
		i++;
	}
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

long ft_get_time_ms(const struct timeval *time)
{
	return ((time->tv_sec * 1000) + (time->tv_usec / 1000));
}

int	ft_verify_death(t_philo *philo)
{
	struct timeval now;

	pthread_mutex_lock(&philo->common->shutdown_mutex);
		if (philo->common->shutdown == 1)
		{
			pthread_mutex_unlock(&philo->common->shutdown_mutex);
			return (1);			
		}		
	pthread_mutex_unlock(&philo->common->shutdown_mutex);

	gettimeofday(&now, NULL);
	pthread_mutex_lock(&philo->common->shutdown_mutex);		
		if (ft_get_time_ms(&now) > ft_get_time_ms(&philo->last_meal) + philo->common->time_to_die)
		{			
			pthread_mutex_lock(&philo->common->printf_mutex);
				printf("%ld %d is died\n", ft_get_time_ms(&now), philo->id_philo);
			pthread_mutex_unlock(&philo->common->printf_mutex);
			philo->common->shutdown = 1;
			pthread_mutex_unlock(&philo->common->shutdown_mutex);
			return (1);
		}
	pthread_mutex_unlock(&philo->common->shutdown_mutex);
	return (0);
}
