/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 08:23:12 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/11 13:49:50 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_init_mutex(t_common **common)
{
	int i;
	int err;

	if (pthread_mutex_init(&(*common)->shutdown_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&(*common)->printf_mutex, NULL))
	{
		pthread_mutex_destroy(&(*common)->shutdown_mutex);
		return (1);
	}
	if (pthread_mutex_init(&(*common)->start_time_mutex, NULL))
	{
		pthread_mutex_destroy(&(*common)->printf_mutex);
		pthread_mutex_destroy(&(*common)->shutdown_mutex);
		return (1);
	}

	i = 0;
	while (i < (*common)->number_of_philosophers)
	{
		err = pthread_mutex_init(&(*common)->forks_mutex[i], NULL);
		if (err)
		{
			/* destruir os que já foram inicializados */
			while (i-- > 0)
				pthread_mutex_destroy(&(*common)->forks_mutex[i]);
			pthread_mutex_destroy(&(*common)->start_time_mutex);
			pthread_mutex_destroy(&(*common)->printf_mutex);
			pthread_mutex_destroy(&(*common)->shutdown_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_init_common(int argc, char *argv[], t_common **common)
{
	*common = (t_common *) malloc(sizeof(t_common));
	if (*common == NULL)
		return (1);
	(*common)->shutdown = 0;
	(*common)->number_of_philosophers = ft_atoi(argv[1]);
	(*common)->time_to_die = ft_atoi(argv[2]);
	(*common)->time_to_eat = ft_atoi(argv[3]);
	(*common)->time_to_sleep = ft_atoi(argv[4]);
	(*common)->number_of_times_must_eat = -1;
	(*common)->start_time = ft_get_time_ms();
	if (argc == 6)
		(*common)->number_of_times_must_eat = ft_atoi(argv[5]);
	(*common)->forks_mutex = (pthread_mutex_t *) \
		malloc((*common)->number_of_philosophers * sizeof(pthread_mutex_t));
	if ((*common)->forks_mutex == NULL)
		return (1);
	if (ft_init_mutex(common) != 0)
	{
		free((*common)->forks_mutex);
		free(*common);
		return (1);
	}
	return (0);
}
