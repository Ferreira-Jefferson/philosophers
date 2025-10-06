/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 08:23:12 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/06 14:14:01 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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
