/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:19:02 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/12 08:53:49 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_exit_all(pid_t *pids, t_common *common)
{
	int	i;
	int	size;

	size = common->number_of_philosophers;
	i = 0;
	while (i < size)
	{
		if (pids[i] > 0)
			kill(pids[i], SIGKILL);
		i++;
	}
	while (wait(NULL) > 0)
		;
	ft_close_all(common);
}

void	ft_verity_death_by_saciety(t_philo *philo)
{
	if (philo->common->number_of_times_must_eat != -1 && \
		philo->number_time_eat >= philo->common->number_of_times_must_eat)
	{
		if (philo->data_sem && philo->data_sem != SEM_FAILED)
			sem_close(philo->data_sem);
		sem_unlink(philo->data_sem_name);
		ft_close_all(philo->common);
		free(philo->common);
		exit(0);
	}
}

void	ft_verity_death_by_time(t_philo *philo)
{
	long	slept;
	long	sleep_ms;

	slept = 0;
	sleep_ms = philo->common->time_to_sleep;
	while (slept < sleep_ms)
	{
		slept++;
		sem_wait(philo->data_sem);
		if (ft_get_time_ms() - philo->last_meal > philo->common->time_to_die)
		{
			sem_wait(philo->common->sem_print);
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
		sem_post(philo->data_sem);
	}
}

void	ft_close_all_2(t_common *common)
{
	if (common->sem_death && common->sem_death != SEM_FAILED)
	{
		sem_close(common->sem_death);
		common->sem_death = SEM_FAILED;
	}
}

void	ft_close_all(t_common *common)
{
	if (!common)
		return ;
	if (common->sem_forks && common->sem_forks != SEM_FAILED)
	{
		sem_close(common->sem_forks);
		common->sem_forks = SEM_FAILED;
	}
	if (common->sem_print && common->sem_print != SEM_FAILED)
	{
		sem_close(common->sem_print);
		common->sem_print = SEM_FAILED;
	}
	if (common->sem_butler && common->sem_butler != SEM_FAILED)
	{
		sem_close(common->sem_butler);
		common->sem_butler = SEM_FAILED;
	}
	ft_close_all_2(common);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_BUTLER);
	sem_unlink(SEM_DEATH);
}
