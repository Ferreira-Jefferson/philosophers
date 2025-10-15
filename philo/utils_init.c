/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 08:23:12 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/14 09:29:32 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_init_common(int argc, char *argv[], t_common *common)
{
	common->number_of_philosophers = ft_atoi(argv[1]);
	common->time_to_die = ft_atoi(argv[2]);
	common->time_to_eat = ft_atoi(argv[3]);
	common->time_to_sleep = ft_atoi(argv[4]);
	common->number_of_times_must_eat = -1;
	if (argc == 6)
		common->number_of_times_must_eat = ft_atoi(argv[5]);
}

void	ft_init_philos(t_common *common, t_philo *philos, \
	t_table *table, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < common->number_of_philosophers)
	{
		philos[i].common = *common;
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].start_time = ft_get_time_ms();
		philos[i].last_meal = ft_get_time_ms();
		philos[i].write_lock = &table->write_lock;
		philos[i].dead_lock = &table->dead_lock;
		philos[i].meal_lock = &table->meal_lock;
		philos[i].dead = &table->dead_flag;
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos[i]
				.common.number_of_philosophers - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		i++;
	}
}

void	ft_init_table(t_table *table, t_philo *philos)
{
	table->dead_flag = 0;
	table->philos = philos;
	pthread_mutex_init(&table->write_lock, NULL);
	pthread_mutex_init(&table->dead_lock, NULL);
	pthread_mutex_init(&table->meal_lock, NULL);
}

void	ft_init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}
