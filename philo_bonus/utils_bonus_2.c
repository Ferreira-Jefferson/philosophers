/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:19:08 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/12 08:28:02 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int ft_check_death(t_philo *philo)
{
	if (philo->common->number_of_times_must_eat == -1)
		return (0);
	sem_wait(philo->data_sem);
		if (philo->number_time_eat >= philo->common->number_of_times_must_eat)
		{
			sem_post(philo->data_sem);
			return (1);			
		}
	sem_post(philo->data_sem);
	return (0);	
}

void	ft_announce_death(t_philo *philo)
{
	sem_wait(philo->common->sem_print);
	printf("%ld %d died\n",
		ft_get_time_ms() - philo->common->start_time + 2,
		philo->id_philo + 1);
	if (philo->data_sem && philo->data_sem != SEM_FAILED)
		sem_close(philo->data_sem);
	sem_unlink(philo->data_sem_name);
	ft_close_all(philo->common);
	free(philo->common);
	exit(1);
}

void	ft_eating(t_philo *philo)
{
	sem_wait(philo->common->sem_butler);
	sem_wait(philo->common->sem_forks);
	ft_print_message(philo, "has taken a fork");
	sem_wait(philo->common->sem_forks);
	ft_print_message(philo, "has taken a fork");
	ft_print_message(philo, "is eating");
	sem_wait(philo->data_sem);
	philo->last_meal = ft_get_time_ms();
	philo->number_time_eat++;
	sem_post(philo->data_sem);
	usleep(philo->common->time_to_eat * 1000);
	sem_post(philo->common->sem_forks);
	sem_post(philo->common->sem_forks);
	sem_post(philo->common->sem_butler);
}

void	ft_sleeping(t_philo *philo)
{
	long	start_sleep;
	long	elapsed;

	ft_print_message(philo, "is sleeping");
	start_sleep = ft_get_time_ms();
	while (1)
	{
		if (ft_check_death(philo))
			exit(0);
		elapsed = ft_get_time_ms() - start_sleep;
		if (elapsed >= philo->common->time_to_sleep)
			break ;
		if (philo->common->number_of_times_must_eat == -1)
		{
			sem_wait(philo->data_sem);
			if (ft_get_time_ms() - philo->last_meal + 1 >= \
				philo->common->time_to_die)
			{
				sem_post(philo->data_sem);
				ft_announce_death(philo);
			}
			sem_post(philo->data_sem);
		}
		usleep(1000);
	}
}
