/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:11:45 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/14 09:10:05 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ft_print_message("has taken a fork", philo, philo->id);
	if (philo->common.number_of_philosophers == 1)
	{
		ft_usleep(philo->common.time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	ft_print_message("has taken a fork", philo, philo->id);
	philo->eating = 1;
	ft_print_message("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = ft_get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->common.time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*ft_philo_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!ft_check_if_any_death(philo))
	{
		ft_eating(philo);
		ft_print_message("is sleeping", philo, philo->id);
		ft_usleep(philo->common.time_to_sleep);
		ft_print_message("is thinking", philo, philo->id);
	}
	return (args);
}

int	ft_thread_create(t_table *table, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &ft_monitor, table->philos) != 0)
		ft_destory_all(table, forks);
	i = 0;
	while (i < table->philos[0].common.number_of_philosophers)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &ft_philo_routine,
				&table->philos[i]) != 0)
			ft_destory_all(table, forks);
		i++;
	}
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		ft_destory_all(table, forks);
	while (i < table->philos[0].common.number_of_philosophers)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			ft_destory_all(table, forks);
		i++;
	}
	return (0);
}
