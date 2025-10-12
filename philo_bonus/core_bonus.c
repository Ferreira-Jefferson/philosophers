/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:01:19 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/12 09:18:09 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	ft_core(t_philo *philo)
{
	if (philo->id_philo % 2 == 0)
		usleep(philo->common->time_to_eat * 500);
	while (1)
	{
		if (ft_check_death(philo))
			exit(0);
		ft_eating(philo);
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
		ft_sleeping(philo);
		ft_verify_death_by_time(philo);
		if (ft_check_death(philo))
			exit(0);
		ft_print_message(philo, "is thinking");
		ft_verify_death_by_time(philo);
	}
}

static void	ft_children(t_common *common, int id)
{
	t_philo	philo;

	philo = (t_philo){0};
	philo.id_philo = id;
	philo.common = common;
	philo.last_meal = ft_get_time_ms();
	ft_generate_sem_name(SEM_DATA_BASE, id, philo.data_sem_name);
	sem_unlink(philo.data_sem_name);
	philo.data_sem = sem_open(philo.data_sem_name, O_CREAT, 0644, 1);
	ft_core(&philo);
}

static void	ft_finish(t_common *common, pid_t *pids)
{
	int		finished_count;
	int		death_occured;
	int		status;

	finished_count = 0;
	death_occured = 0;
	while (finished_count < common->number_of_philosophers)
	{
		if (waitpid(-1, &status, 0) <= 0)
			continue ;
		finished_count++;
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			death_occured = 1;
			break ;
		}
	}
	if (death_occured)
		ft_exit_all(pids, common);
}

void	ft_start(t_common *common)
{
	int		i;
	pid_t	*pids;

	pids = malloc(common->number_of_philosophers * sizeof(pid_t));
	if (!pids)
		return ;
	i = 0;
	while (i < common->number_of_philosophers)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			free(pids);
			ft_children(common, i);
		}
		if (pids[i] < 0)
			break ;
		i++;
	}
	ft_finish(common, pids);
	ft_close_all(common);
	free(pids);
}
