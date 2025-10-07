/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 08:23:12 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/06 16:42:22 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int ft_init_semaphore_philo(t_philo *philo)
{
	sem_unlink(SEM_LAST_MEAL);
	philo->sem_last_meal = sem_open(SEM_LAST_MEAL, O_CREAT, 0644, 1);
	if (philo->sem_last_meal == SEM_FAILED)
	{
		sem_unlink(SEM_LAST_MEAL);
		return (1);
	}
	sem_unlink(SEM_NUMBER_TIME_EAT);
	philo->sem_number_time_eat = sem_open(SEM_NUMBER_TIME_EAT, \
		O_CREAT, 0644, 1);
	if (philo->sem_number_time_eat == SEM_FAILED)
	{
		sem_unlink(SEM_NUMBER_TIME_EAT);
		return (1);
	}
	return (0);
}

int ft_init_semaphore(t_common **common)
{
	int number_philos;

	number_philos = (*common)->number_of_philosophers;
	sem_unlink(SEM_FORKS);
	(*common)->sem_forks = sem_open(SEM_FORKS, O_CREAT, 0644, number_philos);
	if ((*common)->sem_forks == SEM_FAILED)
	{
		sem_unlink(SEM_FORKS);
		return (1);
	}
	sem_unlink(SEM_PRINT);
	(*common)->sem_print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if ((*common)->sem_print == SEM_FAILED)
	{
		sem_unlink(SEM_PRINT);
		return (1);
	}
	return (0);
}

int	ft_init_common(int argc, char *argv[], t_common **common)
{
	(*common)->shutdown = 0;
	(*common)->number_of_philosophers = ft_atoi(argv[1]);
	(*common)->time_to_die = ft_atoi(argv[2]);
	(*common)->time_to_eat = ft_atoi(argv[3]);
	(*common)->time_to_sleep = ft_atoi(argv[4]);
	(*common)->number_of_times_must_eat = -1;
	(*common)->start_time = ft_get_time_ms();
	if (argc == 6)
		(*common)->number_of_times_must_eat = ft_atoi(argv[5]);
	if (ft_init_semaphore(common))
		return (1);
	return (0);
}
