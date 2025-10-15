/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:08:05 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/15 07:36:23 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_verify_death(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (ft_get_time_ms() - philo->last_meal >= time_to_die
		&& philo->eating == 0)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	ft_check_any_died(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].common.number_of_philosophers)
	{
		if (ft_verify_death(&philos[i], philos[i].common.time_to_die))
		{
			ft_print_message("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_if_all_ate(t_philo *philos)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philos[0].common.number_of_times_must_eat == -1)
		return (0);
	while (i < philos[0].common.number_of_philosophers)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].common.number_of_times_must_eat)
			finished_eating++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (finished_eating == philos[0].common.number_of_philosophers)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*ft_monitor(void *args)
{
	t_philo	*philos;

	philos = (t_philo *)args;
	while (1)
		if (ft_check_any_died(philos) == 1 || ft_check_if_all_ate(philos) == 1)
			break ;
	return (args);
}
