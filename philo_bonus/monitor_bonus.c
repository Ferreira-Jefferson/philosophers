/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:25:29 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/08 10:22:56 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	ft_is_satiated(t_philo *philo)
{
	if (philo->number_time_eat >= \
		philo->common->number_of_times_must_eat)
	{
		sem_post(philo->common->sem_butler);
		sem_post(philo->common->sem_forks);
		sem_post(philo->common->sem_forks);
		if (philo->data_sem && philo->data_sem != SEM_FAILED)
			sem_close(philo->data_sem);
		sem_unlink(philo->data_sem_name);
		ft_close_all(philo->common);
		free(philo->common);
		exit(0);
	}
}

static void	ft_verify_death(t_philo *philo)
{
	sem_wait(philo->common->sem_print);
	if (philo->common->number_of_times_must_eat == -1)
	{
		printf("%ld %d died\n", \
			ft_get_time_ms() - philo->common->start_time, \
			philo->id_philo + 1);
		if (philo->data_sem && philo->data_sem != SEM_FAILED)
			sem_close(philo->data_sem);
		sem_unlink(philo->data_sem_name);
		ft_close_all(philo->common);
		free(philo->common);
		exit(1);
	}
	sem_post(philo->common->sem_print);
}

void	*ft_monitor(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		sem_wait(philo->data_sem);
		if (philo->common->number_of_times_must_eat != -1)
			ft_is_satiated(philo);
		else if (ft_get_time_ms() - philo->last_meal > \
			philo->common->time_to_die)
		{
			ft_verify_death(philo);
		}
		sem_post(philo->data_sem);
		usleep(1000);
	}
	return (NULL);
}
