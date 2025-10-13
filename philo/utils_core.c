/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:08:36 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/13 16:59:53 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_create(pthread_t	*thr_philos, pthread_t	*thr_monitor, \
	t_philo *philos, t_common *common)
{
	int		i;
	int		quantity;
	long	start_time;

	quantity = common->number_of_philosophers;
	start_time = ft_get_time_ms();
	i = 0;
	while (i < quantity)
	{
		philos[i].last_meal = start_time;
		philos[i].id_philo = i;
		philos[i].number_time_eat = 0;
		philos[i].common = common;
		pthread_mutex_init(&philos[i].last_meal_mutex, NULL);
		i++;
	}
	i = 0;
	while (i < quantity)
	{
		pthread_create(&thr_philos[i], NULL, &ft_core, &philos[i]);
		i++;
	}
	pthread_create(thr_monitor, NULL, &ft_monitor, philos);
}

void	ft_lock_forks(t_philo *philo)
{
	int	i;
	int qtd;

	qtd = philo->common->number_of_philosophers;
	i = philo->id_philo;

	if (i == qtd - 1) { 
		pthread_mutex_lock(&philo->common->forks_mutex[(i + 1) % qtd]);
		ft_print_message(philo, "has taken a fork");
		pthread_mutex_lock(&philo->common->forks_mutex[i]);
		ft_print_message(philo, "has taken a fork");
	} else {
		pthread_mutex_lock(&philo->common->forks_mutex[i]);
		ft_print_message(philo, "has taken a fork");
		pthread_mutex_lock(&philo->common->forks_mutex[(i + 1) % qtd]);
		ft_print_message(philo, "has taken a fork");
	}
}

void	ft_unlock_forks(t_philo *philo)
{
	int	i;
	int qtd;

	qtd = philo->common->number_of_philosophers;
	i = philo->id_philo;

	if (i == qtd - 1) { 
		pthread_mutex_unlock(&philo->common->forks_mutex[(i + 1) % qtd]);
		pthread_mutex_unlock(&philo->common->forks_mutex[i]);
	} else {
		pthread_mutex_unlock(&philo->common->forks_mutex[i]);
		pthread_mutex_unlock(&philo->common->forks_mutex[(i + 1) % qtd]);
	}
}

int	ft_should_shutdown(t_philo *philo)
{
	int			should_shutdown;
	int			fed;
	long		times_eaten;

	pthread_mutex_lock(&philo->common->shutdown_mutex);
	should_shutdown = philo->common->shutdown;
	pthread_mutex_unlock(&philo->common->shutdown_mutex);
	pthread_mutex_lock(&philo->last_meal_mutex);
	times_eaten = philo->number_time_eat;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	fed = (philo->common->number_of_times_must_eat != -1 \
		&& times_eaten >= philo->common->number_of_times_must_eat);
	return (should_shutdown || fed);
}

void	ft_eating(t_philo *philo)
{
	if (ft_should_shutdown(philo))
		return ;
	ft_lock_forks(philo);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = ft_get_time_ms();
	philo->number_time_eat++;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	ft_print_message(philo, "is eating");
	ft_usleep(philo->common->time_to_eat * 1000);
	ft_unlock_forks(philo);
}

void ft_usleep(int time)
{
	while (time <= 0)
	{
		usleep(time / 10);
		time /= 10;
	}
}