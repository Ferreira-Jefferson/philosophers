/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:08:36 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/03 16:00:00 by jtertuli         ###   ########.fr       */
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

void	ft_get_forks_id(t_philo *philo, int *left_fork, int *right_fork)
{
	int	id;

	id = philo->id_philo;
	*left_fork = id;
	*right_fork = (id + 1) % philo->common->number_of_philosophers;
	if (*left_fork > *right_fork)
	{
		*right_fork = *left_fork ^ *right_fork;
		*left_fork = *left_fork ^ *right_fork;
		*right_fork = *left_fork ^ *right_fork;
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
	
	// Protege a leitura de number_time_eat com o mutex correto
	pthread_mutex_lock(&philo->last_meal_mutex);
	times_eaten = philo->number_time_eat;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	
	fed = (philo->common->number_of_times_must_eat != -1 && 
	       times_eaten >= philo->common->number_of_times_must_eat);
	
	return (should_shutdown || fed);
}

void	ft_eating(t_philo *philo)
{
	int				left_fork;
	int				right_fork;

	ft_get_forks_id(philo, &left_fork, &right_fork);
	pthread_mutex_lock(&philo->common->forks_mutex[left_fork]);
	ft_print_message(philo, "has taken a fork");
	if (philo->common->number_of_philosophers > 1)
	{
		pthread_mutex_lock(&philo->common->forks_mutex[right_fork]);
		ft_print_message(philo, "has taken a fork");
	}
	
	// CRITICAL: Atualiza last_meal ANTES de printar "is eating"
	// e protege com o mutex correto (last_meal_mutex)
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = ft_get_time_ms();
	philo->number_time_eat++;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	
	ft_print_message(philo, "is eating");
	usleep(philo->common->time_to_eat * 1000);
	
	if (philo->common->number_of_philosophers > 1)
		pthread_mutex_unlock(&philo->common->forks_mutex[right_fork]);
	pthread_mutex_unlock(&philo->common->forks_mutex[left_fork]);
}