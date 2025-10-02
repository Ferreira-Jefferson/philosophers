/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:08:05 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/02 10:15:31 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_verify_death(t_philo *philo)
{
	long	stop_by_meal;

	pthread_mutex_lock(&philo->common->shutdown_mutex);
		stop_by_meal = philo->common->number_of_times_must_eat != -1;
	pthread_mutex_unlock(&philo->common->shutdown_mutex);
	if (ft_should_shutdown(philo) || stop_by_meal)
		return (1);
	pthread_mutex_lock(&philo->common->shutdown_mutex);
	if (ft_get_time_ms() > philo->last_meal + philo->common->time_to_die)
	{
		ft_print_message(philo, "is died");
		philo->common->shutdown = 1;
		pthread_mutex_unlock(&philo->common->shutdown_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->common->shutdown_mutex);
	return (0);
}

void	*ft_monitor(void *args)
{
	t_philo	*philos;
	int		number_of_philos;

	philos = (t_philo *) args;
	number_of_philos = 0;
	while (1)
	{
		number_of_philos = philos[0].common->number_of_philosophers;
		while (--number_of_philos >= 0)
		{
			if (ft_verify_death(&philos[number_of_philos]))
				return (NULL);
		}
	}
	return (NULL);
}
