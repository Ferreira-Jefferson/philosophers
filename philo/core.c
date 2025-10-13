/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:11:45 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/13 16:29:38 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_start(t_common **common)
{
	int			quantity;
	pthread_t	*thr_philos;
	pthread_t	thr_monitor;
	t_philo		*philos;
	int			i;

	quantity = (*common)->number_of_philosophers;
	philos = (t_philo *) malloc(quantity * sizeof(t_philo));
	if (!philos)
		return ;
	thr_philos = (pthread_t *) malloc(quantity * sizeof(pthread_t));
	if (!thr_philos)
		return (free(philos));
	ft_create(thr_philos, &thr_monitor, philos, *common);
	ft_join(quantity, thr_philos, &thr_monitor);
	i = 0;
	while (i < quantity)
	{
		pthread_mutex_destroy(&philos[i].last_meal_mutex);
		i++;
	}
	ft_destroy_mutex(*common);
	free(philos);
	free(thr_philos);
}

void	*ft_core(void *args)
{
	t_philo	*philo;

	philo = (t_philo *) args;
	while (!ft_should_shutdown(philo))
	{
		ft_eating(philo);
		if (!ft_should_shutdown(philo))
		{
			ft_print_message(philo, "is sleeping");
			ft_usleep(philo->common->time_to_sleep * 1000);
		}
		if (!ft_should_shutdown(philo))
		{
			ft_print_message(philo, "is thinking");
			ft_usleep(100);
		}
	}
	return (NULL);
}
