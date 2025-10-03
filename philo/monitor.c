/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:08:05 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/03 16:00:00 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_verify_death(t_philo *philo)
{
	long	last_meal_time;
	long	current_time;
	int		is_dead;

	pthread_mutex_lock(&philo->common->shutdown_mutex);
	if (philo->common->shutdown)
	{
		pthread_mutex_unlock(&philo->common->shutdown_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->common->shutdown_mutex);
	pthread_mutex_lock(&philo->last_meal_mutex);
	last_meal_time = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	current_time = ft_get_time_ms();
	is_dead = (current_time - last_meal_time) > philo->common->time_to_die;
	if (is_dead)
	{
		pthread_mutex_lock(&philo->common->shutdown_mutex);
		if (!philo->common->shutdown)
		{
			philo->common->shutdown = 1;
			pthread_mutex_unlock(&philo->common->shutdown_mutex);
			ft_print_message(philo, "died");
			return (1);
		}
		pthread_mutex_unlock(&philo->common->shutdown_mutex);
	}
	return (0);
}

static int	ft_check_all_fed(t_philo *philos, int num_philos)
{
	int		i;
	int		all_fed;
	long	times_eaten;

	if (philos[0].common->number_of_times_must_eat == -1)
		return (0);
	all_fed = 1;
	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_lock(&philos[i].last_meal_mutex);
		times_eaten = philos[i].number_time_eat;
		pthread_mutex_unlock(&philos[i].last_meal_mutex);

		if (times_eaten < philos[0].common->number_of_times_must_eat)
		{
			all_fed = 0;
			break;
		}
		i++;
	}
	if (all_fed)
	{
		pthread_mutex_lock(&philos[0].common->shutdown_mutex);
		philos[0].common->shutdown = 1;
		pthread_mutex_unlock(&philos[0].common->shutdown_mutex);
		return (1);
	}
	return (0);
}

void	*ft_monitor(void *args)
{
	t_philo	*philos;
	int		number_of_philos;
	int		i;

	philos = (t_philo *) args;
	number_of_philos = philos[0].common->number_of_philosophers;
	while (1)
	{
		i = 0;
		while (i < number_of_philos)
		{
			if (ft_verify_death(&philos[i]))
				return (NULL);
			i++;
		}
		if (ft_check_all_fed(philos, number_of_philos))
			return (NULL);
		usleep(500);
	}
	return (NULL);
	
}